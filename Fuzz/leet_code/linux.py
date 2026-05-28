import os
import re
import shutil
import invoke
import commandscript


@commandscript.script_task()
def clean(ctx):
    """
    Clean Conan's data for LeetCode
    """
    pass


@commandscript.script_task(
    help={
        "debug": "if set configuration type will be DEBUG (else RELEASE)",
    },
)
def configure(ctx, debug=True):
    """
    Configure LeetCode-project
    """
    pass


@commandscript.script_task(
    help={
        "debug": "if set build type will be DEBUG, else RELEASE (by default DEBUG)",
        "target": "defines name of target to build (by default ALL)",
        "jobs": "defines count parallel buildings (by default 8)",
    },
)
def build(ctx, debug=True, target="all", jobs=8):
    """
    Build LeetCode-project
    """
    pass


@commandscript.script_task(
    help={
        "debug": 'if set build type will be DEBUG, else RELEASE (by default DEBUG)',
        "target": 'defines regexpr-name of target to launch (by default ".+")',
        "gtest_filter": 'defines regexpr-filter for tests in targets (by default ".+")',
    },
)
def launch(ctx, debug=True, target=".+", gtest_filter="*"):
    """
    Launch targets of LeetCode-project
    """
    pass


@commandscript.script_task(
    help={
        "clean": "should clean all temporary files before checking",
        "debug": "if set build type will be DEBUG, else RELEASE (by default DEBUG)",
        "detect_conan_profile": "detect Conan's profile for the fist time (by default False)",
        "target": 'defines regexpr-name of target to launch (by default ".+")',
    },
)
def full_check(ctx, clean=False, debug=True, detect_conan_profile=False, target=".+"):
    """
    Full-check LeetCode-project
    """
    pass
