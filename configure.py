#!/usr/bin/env python3

import os
import shutil
import subprocess
import sys

# Define the necessary commands
REQUIRED_COMMANDS = ["flex", "clang", "cmake", "make", "bison"]

def check_commands():
    for cmd in REQUIRED_COMMANDS:
        if shutil.which(cmd) is None:
            print(f"Error: {cmd} is not installed. Please install it and try again.")
            sys.exit(1)

def setup_sources():
    src_dir = os.path.join("..", "src")
    include_dir = os.path.join("..", "include")
    os.chdir("utils")
    subprocess.run(["flex", "lexer.l"], check=True)
    subprocess.run(["bison", "-d", "parser.y"], check=True)
    shutil.move("lex.yy.c", os.path.join(src_dir, "lex.yy.c"))
    shutil.move("parser.tab.c", os.path.join(src_dir, "parser.tab.c"))
    shutil.move("parser.tab.h", os.path.join(include_dir, "parser.tab.h"))
    os.chdir("..")

def run_cmake():
    os.makedirs("build", exist_ok=True)
    os.chdir("build")
    subprocess.run(["cmake", ".."], check=True)

def main():
    check_commands()
    setup_sources()
    run_cmake()
    print("Makefile generated!")

if __name__ == "__main__":
    main()

