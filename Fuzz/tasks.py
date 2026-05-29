import pathlib
import invoke
import commandscript


commandscript.ENV_CONTEXT\
    .add_env_var('PROJECT_GIT_DIR', str(pathlib.Path(f'{__file__}').parent.parent))\
    .add_env_var('PROJECT_FUZZ_DIR', '${PROJECT_GIT_DIR}/Fuzz')\
    .add_env_var('COMMANDSCRIPT_SCRIPT_DIR', '${PROJECT_GIT_DIR}/.generated')\
    .add_env_var('PROJECT_ARTIFACTS_DIR', '${PROJECT_GIT_DIR}/.artifacts')\
    .add_env_var('CONAN_PROFILES_DIR', '${PROJECT_GIT_DIR}/conan')\
    .add_env_var('LEET_CODE_DIR', '${PROJECT_GIT_DIR}/LeetCode')\
    .add_env_var('CPP_DETAILS_DIR', '${PROJECT_GIT_DIR}/CppDetails')


@commandscript.script_task()
def get_info(ctx):
    """
    Print to console information about active configuration of commandsript-tasks
    """
    names = [value.name for value in commandscript.ENV_CONTEXT.values()]
    hold_values = [value.hld for value in commandscript.ENV_CONTEXT.values()]
    expanded_values = [value.exp for value in commandscript.ENV_CONTEXT.values()]
    width = max(max(len(key) for key in names), max(len(item) for item in hold_values), max(len(item) for item in expanded_values), 25)
    commandscript.info.log_line("Active environment configuration:")
    commandscript.info.log_line(f"| {'Env-var name':<{width}} | {'Env-var hold-value':<{width}} | {'Env-var expanded-value':<{width}} |")
    commandscript.info.log_line(f"|-{'-' * width}-|-{'-' * width}-|-{'-' * width}-|")
    for i in range(len(names)):
        key = names[i]
        hold_value = hold_values[i]
        expanded_value = expanded_values[i]
        if expanded_value == hold_value:
            expanded_value = '-'
        commandscript.info.log_line(f"| {key:<{width}} | {hold_value:<{width}} | {expanded_value:<{width}} |")


namespace = invoke.Collection()
namespace.add_task(get_info, name="get-info")

import code_utils

namespace.add_collection(code_utils.collection, name='code-utils')

import conan_task

namespace.add_collection(conan_task.collection, name='conan')

import leet_code

namespace.add_collection(leet_code.collection, name='leet-code')

import cpp_details

namespace.add_collection(cpp_details.collection, name='cpp-details')
