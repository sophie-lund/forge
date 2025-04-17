#!/bin/bash

# Copyright 2025 Sophie Lund
#
# This file is part of Forge.
#
# Forge is free software: you can redistribute it and/or modify it under the terms of the GNU
# General Public License as published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.
#
# Forge is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
# the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
# Public License for more details.
#
# You should have received a copy of the GNU General Public License along with Forge. If not, see
# <https://www.gnu.org/licenses/>.

set -e

function _verify_log_message {
    local message="$*"

    if [ -n "$(echo "${message}" | grep -E "^[a-z].+")" ]; then
        die_error "Log messages must start with a capital letter: '${message}'"
    fi

    if [ -n "$(echo "${message}" | grep -E "[^.]\\.$")" ]; then
        die_error "Log messages must not end with a period '.': '${message}'"
    fi
}

# Usage: log_info <message...>
#
# Logs some info to the console.
function log_info {
    _verify_log_message "$*"

    echo -e "\033[0;90m[\033[1;32mINFO \033[0;90m]\033[1;37m $*\033[0m"
}

# Usage: log_warning <message...>
#
# Logs a warning to the console.
function log_warning {
    _verify_log_message "$*"

    echo -e "\033[0;90m[\033[1;33mWARN \033[0;90m]\033[1;37m $*\033[0m"
}

# Usage: log_error <message...>
#
# Logs an error to the console, but does nothing.
function log_error {
    _verify_log_message "$*"

    echo -e "\033[0;90m[\033[1;31mERROR\033[0;90m]\033[1;37m $*\033[0m"
}

# Usage: die error <message...>
#
# Logs an error to the console and then exists with status 1.
function die_error {
    log_error "$*"
    exit 1
}

# Usage: log_status <message...>
#
# Logs a status line to the console - used to separate sections.
function log_status {
    _verify_log_message "$*"

    echo -e "\033[0;90m[\033[1;36m=====\033[0;90m]\033[1;37m $*\033[0m"
}

# Usage: log_step <message...>
#
# Logs a step progress indicator to the console.
function log_step {
    local step="$1"
    local total="$2"
    local message="$3"

    if [ -n "$4" ]; then
        die_error "Function 'log_step' requires exactly 3 arguments"
    fi

    _verify_log_message "${message}"

    printf "\033[0;90m[\033[1;36m%2s\033[0;90m/\033[1;36m%-2s\033[0;90m]\033[1;37m %s\033[0m\n" "${step}" "${total}" "${message}"
}

# Usage: run_steps <steps...>
#
# Each step is a function that is called. It must be of this form:
#
# function step_<name> {
#     case "$1" in
#         title)
#             echo "<name>"
#             ;;
#         run)
#             # ...
#             ;;
#     esac
# }
function run_steps {
    local steps=()
    for step in "$@"; do
        if ${step} enabled; then
            steps+=("${step}")
        fi
    done

    local index="1"
    for step in "${steps[@]}"; do
        if [ "$(type -t ${step})" != "function" ]; then
            die_error "Step '${step}' is not a function"
        fi

        log_step "${index}" "${#steps[@]}" "$(${step} title)"
        ${step} run

        index="$((index + 1))"
    done
}

# Usage: print_output_on_error <command...>
#
# Runs a command and prints the output only if the command fails.
function print_output_on_error {
    local tempfile="$(mktemp)" || return

    if ! "$@" >"$tempfile" 2>&1; then
        cat "$tempfile"
        rm -f "$tempfile"
        return 1
    fi

    rm -f "$tempfile"
}
