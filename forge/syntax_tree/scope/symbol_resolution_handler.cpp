// Copyright 2025 Sophie Lund
//
// This file is part of Forge.
//
// Forge is free software: you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.
//
// Forge is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
// A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with
// Forge. If not, see <https://www.gnu.org/licenses/>.

#include <forge/core/tracing.hpp>
#include <forge/syntax_tree/scope/symbol_resolution_handler.hpp>

namespace forge {
Handler::Output SymbolResolutionHandler::on_enter(Handler::Input& input) {
  trace("SymbolResolutionHandler")
      << "entering " << input.node()->kind << std::endl;
  trace_indent();

  std::optional<std::pair<SymbolMode, std::string>> result =
      input.node()->on_get_symbol();

  if (!result.has_value()) {
    return typename Handler::Output();
  }

  const Scope* parent_scope = try_find_parent_scope(input);

  if (parent_scope == nullptr) {
    input.message_context().emit(
        input.node()->source_range, SEVERITY_ERROR, "???",
        "no surrounding scope in which to declare/resolve symbol");
    return Handler::Output();
  }

  if (result.value().first == SymbolMode::declares) {
    bool was_added = parent_scope->add(result.value().second, input.node());

    if (!was_added) {
      input.message_context().emit(input.node()->source_range, SEVERITY_ERROR,
                                   "???", "redeclaration of existing symbol");
    }
  } else if (result.value().first == SymbolMode::references) {
    std::shared_ptr<Node> referenced = parent_scope->get(result.value().second);

    if (referenced) {
      input.node()->on_resolve_symbol(referenced);
    } else {
      input.message_context().emit(input.node()->source_range, SEVERITY_ERROR,
                                   "???", "use of undeclared symbol");
    }
  }

  return Handler::Output();
}

Handler::Output SymbolResolutionHandler::on_leave(Handler::Input&) {
  trace_dedent();

  return Handler::Output();
}

const Scope* SymbolResolutionHandler::try_find_parent_scope(
    Handler::Input& input) {
  for (auto it = input.stack().rbegin(); it != input.stack().rend(); ++it) {
    std::shared_ptr<Scope>* scope_pointer =
        const_cast<Node&>(it->get()).on_get_scope_field_pointer();

    if (scope_pointer != nullptr) {
      if (*scope_pointer == nullptr) {
        for (auto it2 = it + 1; it2 != input.stack().rend(); ++it2) {
          std::shared_ptr<Scope>* scope_pointer2 =
              const_cast<Node&>(it2->get()).on_get_scope_field_pointer();

          if (scope_pointer2 != nullptr && *scope_pointer2 != nullptr) {
            *scope_pointer = std::make_shared<Scope>(
                *scope_pointer2, it->get().on_get_scope_flags());
            break;
          }
        }

        if (*scope_pointer == nullptr) {
          *scope_pointer =
              std::make_shared<Scope>(nullptr, it->get().on_get_scope_flags());
        }
      }

      return scope_pointer->get();
    }
  }

  return nullptr;
}
}  // namespace forge
