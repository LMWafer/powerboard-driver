import argparse
import json
from loguru import logger
import os
from parse import parse
import pathlib
import shutil
import subprocess
import sys
from tqdm import tqdm

# sys.tracebacklimit = 0
config_path = None


def save_config(config: dict) -> bool:
    global config_path
    json.dump(config, open(config_path, "w"), indent=4)
    return True

def build_interactive():
    # Incremental manual build with CLI inside a container 
    # (1) Copy container CLI history with `history` command
    # (2) Commit current container to an image 
    pass

def build(args: argparse.Namespace, config: dict) -> None:
    global config_path
    #-> Throw function message
    logger.info("Starting image build procedure...")
    #-> Retrieve root path
    root = args.root
    #-> (1) Execute tests
    # ...

    #-[] (2) Check files
    #-> Check for Dockerfile
    logger.info("Looking for Dockerfile...")
    dockerfile_path = os.path.join(root, config["dev"]["dockerfile"])
    if not os.path.exists(dockerfile_path):
        raise FileNotFoundError("Dockerfile -> ", dockerfile_path)
    logger.success("Dockerfile found !")
    #-> Check for build context files
    #-! next version : print all missing files instead of crashing at first missing one
    logger.info("Looking for build context files...")
    build_context_content = config["dev"]["build_context_content"]
    message_end="..."
    if build_context_content:
        for source_path in tqdm(build_context_content, "Check progress"):
            if not os.path.isabs(source_path):
                idx = build_context_content.index(source_path)
                #-? build_context_content[idx] is for files copying for loop, source_path is for next line
                build_context_content[idx] = source_path = os.path.join(root, source_path)
            if not os.path.exists(source_path):
                logger.warning("Build context file not found:", source_path)
                sys.exit()
        logger.success("Build context files found !")
    else:
        logger.info("No build context file requested !")
        message_end = " although it is empty, to speed up build..."
    
    #-[] (3) Create build context directory
    #-! Do not recreate and copy if files are already in + option to force recreation
    logger.info("Creating build context" + message_end)
    build_context_path = os.path.join(root, config["dev"]["build_context_path"])
    if not os.path.exists(build_context_path):
        os.mkdir(build_context_path)

    #-[] (4) Copy build context files in build context directory
    for source_path in tqdm(build_context_content, "Copying progess"):
        filename = os.path.basename(source_path)
        dest_path = os.path.join(build_context_path, filename)
        shutil.copyfile(source_path, dest_path)
    logger.success("Build context created !")

    #-[] (5) Configure image tag
    #-> Retrieve version
    logger.info("Configuring build version...")
    current_version = config["dev"]["image_version"]
    current_version = parse("{major:d}.{minor:d}.{patch:d}-{build:d}", current_version).named
    version_raised = args.version
    #-> Update build version before starting build
    #-! Be able to tell what version you are working on with this builder
    current_version["build"] += 1
    if version_raised != "same":
        current_version[version_raised] += 1
    #-> Create image tag
    image_name = config["dev"]["image_name"]
    image_version= "{major}.{minor}.{patch}-{build}".format(**current_version)
    image_tag = image_name + ":" + image_version
    logger.success("Build version configured !")

    #-[] (6) Build image
    logger.info(f"Starting image build with")
    logger.debug("Build info")
    logger.debug(f"  Image tag: {image_tag}")
    logger.debug(f"  Dockerfile: {dockerfile_path}")
    logger.debug(f"  Build context: {build_context_path}")
    logger.debug(f"↓↓↓ Build output ↓↓↓")
    no_cache = ""
    if args.no_cache:
        no_cache = "--no-cache"
    #-! Store docker built command's base argument so that baker only takes care of changing arguments (names, tags, files)
    #-! Save build output if needed
    command = f"docker build -t {image_tag} -f {dockerfile_path} {no_cache} {build_context_path}"
    result = subprocess.run(command, shell=True, stderr=subprocess.PIPE)
    logger.debug("↑↑↑ Build output ↑↑↑")
    config["dev"]["image_version"] = image_version
    #-! Save image version into Dockerfile in order to "hardcode" it within the image
    save_config(config)
    #-! Intercept KeyboardInterrupr (CTRL + C) to save build info before closing
    if result.stderr:
        logger.warning("Image build failed !")
        logger.debug(f"↓↓↓ Build error ↓↓↓")
        sys.tracebacklimit = 0
        raise Exception(result.stderr, )
    #-! Keep track of wether or not build succeeded
    logger.success(f"Image built with tag '{image_tag}' !")

    #-[] (7) If success update version and commit

    #-[] (8) Return
    #-? build context directory is not removed since it may help for debug
    #-! Before commiting copy all files used in the procedure in case of modifications during the build, yeah LM sucks...
    #-! If image is accepted, change tag in docker-compose.yml (start part) and Makefile (container access part)

def init(args):
    #-[] (0) Ask for user and project info ? 
    #-[] (1) Create project directories tree
    #-[] (2) Populate tree (Makefile, backer config, Dockerfile, docker-compose)
    pass

def add(args):
    pass

def activate(args):
    pass

def builders(args):
    pass

def create_config():
    j = {}
    j["dev"] = {"image_name": "author/basename-dev",
                "image_version": "1.0.0-1",
                "dockerfile" : "img/Dockerfile-dev",
                "build_context_path": "img/build_context_dev/",
                "build_context_content":     []}
    j["run"] = {"image_name": "author/basename-run",
                "image_version": "1.0.0-1",
                "app_version":       "0.0.0",
                "dockerfile" : "img/Dockerfile-run",
                "build_context_path": "img/build_context_run/",
                "build_context_content":     []}
    json.dump(j, open("builder_config.json", "w"), indent=4)

def main():
    global config_path
    #-[] Define input arguments
    #-! add a configure mode to initialize the "repo"
    parser = argparse.ArgumentParser(prog="baker", description="Intelligent Docker images builder", epilog="Still in developpment")
    parser.add_argument("--root", "-r",
                        required=False, type=pathlib.Path, default="./", metavar="ROOT_DIR",
                        help="directory where to execute command")
    subparsers = parser.add_subparsers(title="sub-commands", description="valid sub-commands", help="sub-command help")
    
    init_parser = subparsers.add_parser("add", help="initialize project directory")
    init_parser.set_defaults(func=init)
    init_parser.add_argument("name",
                            type=str, metavar="NAME",
                            help="project name")
    init_parser.add_argument("language", 
                            type=str, metavar="LANG", choices=["python", "cpp", "python-cpp"],
                            help="project's main language")
    init_parser.add_argument("dockerize", 
                            type=bool, metavar="DOCKER",
                            help="wether to dockerize project or not")

    add_parser = subparsers.add_parser("add", help="create an image builder")
    add_parser.set_defaults(func=add)
    add_parser.add_argument("name",
                            type=str, metavar="NAME",
                            help="builder name")

    activate_parser = subparsers.add_parser("activate", help="activate an image builder")
    activate_parser.set_defaults(func=activate)
    activate_parser.add_argument("name",
                                 type=str, metavar="NAME",
                                 help="builder name")

    builders_parser = subparsers.add_parser("builders", aliases=["ls", "ps"], help="list available builders")
    builders_parser.set_defaults(func=builders)

    build_parser = subparsers.add_parser("build", help="build development image")
    build_parser.set_defaults(func=build)
    build_parser.add_argument("--version", "-ver", "-v",
                              required=False, type=str, default="same", choices=["same", "major", "minor", "patch"], metavar="VERSION",
                              help="version to raise")
    build_parser.add_argument("--no-cache",
                              required=False, action="store_true",
                              help="version to raise")

    #-[] Retrieve input arguments
    os.system("clear")
    logger.info("Welcome to baker, intelligent Docker images builder !")
    args = parser.parse_args()
    root = args.root

    #-[] Process input arguments
    config_path = os.path.join(root, ".baker_files/builder_config.json")
    config = json.load(open((config_path), "r"))
    args.func(args, config)
    

if __name__ == "__main__":
    main()