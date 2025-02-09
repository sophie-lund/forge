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

#include <forge/core/Tracing.hpp>

namespace forge::syntaxtree {
template <typename TBaseNode>
typename Handler<TBaseNode>::Output SymbolResolutionHandler<TBaseNode>::onEnter(
    typename Handler<TBaseNode>::Input& input) {
  core::trace("SymbolResolutionHandler") << "entering node" << std::endl;
  core::traceIndent();

  std::optional<std::pair<SymbolMode, std::string>> result =
      input.node()->onGetSymbol();

  if (!result.has_value()) {
    return typename Handler<TBaseNode>::Output();
  }

  const Scope<TBaseNode>* parentScope = tryFindParentScope(input);

  if (parentScope == nullptr) {
    input.messageContext().emit(
        input.node()->sourceRange, messaging::SEVERITY_ERROR, "???",
        "no surrounding scope in which to declare/resolve symbol");
    return typename Handler<TBaseNode>::Output();
  }

  if (result.value().first == SymbolMode::Declares) {
    bool wasAdded = parentScope->add(result.value().second, input.node());

    if (!wasAdded) {
      input.messageContext().emit(input.node()->sourceRange,
                                  messaging::SEVERITY_ERROR, "???",
                                  "redeclaration of existing symbol");
    }
  } else if (result.value().first == SymbolMode::References) {
    std::shared_ptr<TBaseNode> referenced =
        parentScope->get(result.value().second);

    if (referenced) {
      input.node()->onResolveSymbol(referenced);
    } else {
      input.messageContext().emit(input.node()->sourceRange,
                                  messaging::SEVERITY_ERROR, "???",
                                  "use of undeclared symbol");
    }
  }

  return typename Handler<TBaseNode>::Output();
}

template <typename TBaseNode>
typename Handler<TBaseNode>::Output SymbolResolutionHandler<TBaseNode>::onLeave(
    typename Handler<TBaseNode>::Input&) {
  core::traceDedent();

  return typename Handler<TBaseNode>::Output();
}

template <typename TBaseNode>
const Scope<TBaseNode>* SymbolResolutionHandler<TBaseNode>::tryFindParentScope(
    typename Handler<TBaseNode>::Input& input) {
  for (auto it = input.stack().rbegin(); it != input.stack().rend(); ++it) {
    std::shared_ptr<Scope<TBaseNode>>* scopePointer =
        const_cast<TBaseNode&>(it->get()).onGetScopeFieldPointer();

    if (scopePointer != nullptr) {
      if (*scopePointer == nullptr) {
        for (auto it2 = it + 1; it2 != input.stack().rend(); ++it2) {
          std::shared_ptr<Scope<TBaseNode>>* scopePointer2 =
              const_cast<TBaseNode&>(it2->get()).onGetScopeFieldPointer();

          if (scopePointer2 != nullptr && *scopePointer2 != nullptr) {
            *scopePointer = std::make_shared<Scope<TBaseNode>>(
                *scopePointer2, it->get().onGetScopeFlags());
            break;
          }
        }

        if (*scopePointer == nullptr) {
          *scopePointer = std::make_shared<Scope<TBaseNode>>(
              nullptr, it->get().onGetScopeFlags());
        }
      }

      return scopePointer->get();
    }
  }

  return nullptr;
}
}  // namespace forge::syntaxtree
