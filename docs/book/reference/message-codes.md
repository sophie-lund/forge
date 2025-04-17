<!--
Copyright 2025 Sophie Lund

This file is part of Forge.

Forge is free software: you can redistribute it and/or modify it under the terms of the GNU
General Public License as published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

Forge is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
Public License for more details.

You should have received a copy of the GNU General Public License along with Forge. If not, see
<https://www.gnu.org/licenses/>.
-->

# Message codes

Message codes are used to identify specific messages in the Forge codebase. They are all of the form `<SEVERITY><PREFIX><NUMBER>`. For example, `ESY001` has severity `E` for error, prefix `SY` for syntax, and number `001`.

See [`forge_message_emitters.hpp`](https://github.com/sophie-lund/forge/blob/main/forge/language/forge_message_emitters.hpp) for the full list of message codes.

## Severity codes

| Severity code | Description |
| ------------- | ----------- |
| `E`           | Error       |
| `W`           | Warning     |
| `F`           | Fatal       |

## Prefix codes

| Prefix code | Description |
| ----------- | ----------- |
| `IO`        | File I/O    |
| `IN`        | Internal    |
| `SY`        | Syntax      |
| `SC`        | Scope       |
| `TY`        | Type        |

!!! warning

    `IN` is reserved for internal compiler issues. You should never see them under normal circumstances. If you do, please report it as a bug.
