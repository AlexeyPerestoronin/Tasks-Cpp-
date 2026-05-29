import commandscript

PROJECT_NAME = 'CppDetails'


def get_project_build_dir(debug=True, hold=True):
    build_type = "Debug" if debug else "Release"
    if hold:
        return f"{commandscript.ENV_CONTEXT.PROJECT_ARTIFACTS_DIR.name}/.build_{PROJECT_NAME}_{build_type}"
    else:
        return f"{commandscript.ENV_CONTEXT.PROJECT_ARTIFACTS_DIR.exp}/.build_{PROJECT_NAME}_{build_type}"


@commandscript.script_task(
    help={
        "debug": "if set configuration type will be DEBUG, else RELEASE (by default: TRUE)",
    })
def configure(ctx, debug=True):
    """
    Configure CppDetails-project
    """
    raise RuntimeError('not implemented!')


@commandscript.script_task(
    help={
        "debug": "if set build type will be DEBUG, else RELEASE (by default: TRUE)",
        "target": "defines name of target to build (by default: ALL)",
        "jobs": "defines count parallel buildings (by default: 8)",
    }, )
def build(ctx, debug=True, target="all", jobs=8):
    """
    Build CppDetails-project
    """
    raise RuntimeError('not implemented!')
