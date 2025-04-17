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

#include <forgec/forge_message_emitters.hpp>
#include <forgec/parsing/forge_lexer.hpp>
#include <forgec/parsing/forge_token_kind.hpp>
#include <langtools/core/assert.hpp>
#include <langtools/core/unicode.hpp>

namespace forge {
ForgeLexer::ForgeLexer() : BaseLexer() {}

void ForgeLexer::onLexOne(lt::LexerContext& context) {
  std::u16string_view next = context.peek_next_grapheme_cluster();

  LT_ASSERT(!next.empty(), "grapheme clusters cannot be empty");

  if (next == u"!") {
    context.read_next_grapheme_cluster();
    if (context.are_more_grapheme_clusters() &&
        context.peek_next_grapheme_cluster() == u"=") {
      context.read_next_grapheme_cluster();
      context.emit_token(TOKEN_NE);
    } else {
      context.emit_token(TOKEN_BOOL_NOT);
    }
  } else if (next == u"&") {
    context.read_next_grapheme_cluster();
    if (context.are_more_grapheme_clusters() &&
        context.peek_next_grapheme_cluster() == u"&") {
      context.read_next_grapheme_cluster();
      context.emit_token(TOKEN_BOOL_AND);
    } else if (context.are_more_grapheme_clusters() &&
               context.peek_next_grapheme_cluster() == u"=") {
      context.read_next_grapheme_cluster();
      context.emit_token(TOKEN_BIT_AND_ASSIGN);
    } else {
      context.emit_token(TOKEN_BIT_AND);
    }
  } else if (next == u"|") {
    context.read_next_grapheme_cluster();
    if (context.are_more_grapheme_clusters() &&
        context.peek_next_grapheme_cluster() == u"|") {
      context.read_next_grapheme_cluster();
      context.emit_token(TOKEN_BOOL_OR);
    } else if (context.are_more_grapheme_clusters() &&
               context.peek_next_grapheme_cluster() == u"=") {
      context.read_next_grapheme_cluster();
      context.emit_token(TOKEN_BIT_OR_ASSIGN);
    } else {
      context.emit_token(TOKEN_BIT_OR);
    }
  } else if (next == u"^") {
    context.read_next_grapheme_cluster();
    if (context.are_more_grapheme_clusters() &&
        context.peek_next_grapheme_cluster() == u"=") {
      context.read_next_grapheme_cluster();
      context.emit_token(TOKEN_BIT_XOR_ASSIGN);
    } else {
      context.emit_token(TOKEN_BIT_XOR);
    }
  } else if (next == u"~") {
    context.read_next_grapheme_cluster();
    context.emit_token(TOKEN_BIT_NOT);
  } else if (next == u"+") {
    context.read_next_grapheme_cluster();
    if (context.are_more_grapheme_clusters() &&
        context.peek_next_grapheme_cluster() == u"=") {
      context.read_next_grapheme_cluster();
      context.emit_token(TOKEN_ADD_ASSIGN);
    } else {
      context.emit_token(TOKEN_ADD);
    }
  } else if (next == u"-") {
    context.read_next_grapheme_cluster();
    if (context.are_more_grapheme_clusters() &&
        context.peek_next_grapheme_cluster() == u"=") {
      context.read_next_grapheme_cluster();
      context.emit_token(TOKEN_SUB_ASSIGN);
    } else if (context.are_more_grapheme_clusters() &&
               context.peek_next_grapheme_cluster() == u">") {
      context.read_next_grapheme_cluster();
      context.emit_token(TOKEN_RARROW);
    } else {
      context.emit_token(TOKEN_SUB);
    }
  } else if (next == u"*") {
    context.read_next_grapheme_cluster();
    if (context.are_more_grapheme_clusters() &&
        context.peek_next_grapheme_cluster() == u"*") {
      context.read_next_grapheme_cluster();
      if (context.are_more_grapheme_clusters() &&
          context.peek_next_grapheme_cluster() == u"=") {
        context.read_next_grapheme_cluster();
        context.emit_token(TOKEN_EXP_ASSIGN);
      } else {
        context.emit_token(TOKEN_EXP);
      }
    } else if (context.are_more_grapheme_clusters() &&
               context.peek_next_grapheme_cluster() == u"=") {
      context.read_next_grapheme_cluster();
      context.emit_token(TOKEN_MUL_ASSIGN);
    } else {
      context.emit_token(TOKEN_MUL);
    }
  } else if (next == u"/") {
    context.read_next_grapheme_cluster();
    if (context.are_more_grapheme_clusters() &&
        context.peek_next_grapheme_cluster() == u"=") {
      context.read_next_grapheme_cluster();
      context.emit_token(TOKEN_DIV_ASSIGN);
    } else if (context.are_more_grapheme_clusters() &&
               context.peek_next_grapheme_cluster() == u"/") {
      while (context.are_more_grapheme_clusters()) {
        next = context.peek_next_grapheme_cluster();

        LT_ASSERT(!next.empty(), "grapheme clusters cannot be empty");

        if (next == u"\n") {
          context.read_next_grapheme_cluster();
          break;
        } else {
          context.read_next_grapheme_cluster();
        }
      }

      context.skip_token();
    } else if (context.are_more_grapheme_clusters() &&
               context.peek_next_grapheme_cluster() == u"*") {
      context.read_next_grapheme_cluster();

      std::u16string_view last = u"";
      bool closed_correctly = false;

      while (context.are_more_grapheme_clusters()) {
        next = context.peek_next_grapheme_cluster();

        LT_ASSERT(!next.empty(), "grapheme clusters cannot be empty");

        if (next == u"/" && last == u"*") {
          context.read_next_grapheme_cluster();
          closed_correctly = true;
          break;
        } else {
          last = next;
          context.read_next_grapheme_cluster();
        }
      }

      if (!closed_correctly) {
        emit_syntax_error_unclosed_block_comment(context.message_context(),
                                                 context.current_range());
      }

      context.skip_token();
    } else {
      context.emit_token(TOKEN_DIV);
    }
  } else if (next == u"%") {
    context.read_next_grapheme_cluster();
    if (context.are_more_grapheme_clusters() &&
        context.peek_next_grapheme_cluster() == u"=") {
      context.read_next_grapheme_cluster();
      context.emit_token(TOKEN_MOD_ASSIGN);
    } else {
      context.emit_token(TOKEN_MOD);
    }
  } else if (next == u"=") {
    context.read_next_grapheme_cluster();
    if (context.are_more_grapheme_clusters() &&
        context.peek_next_grapheme_cluster() == u"=") {
      context.read_next_grapheme_cluster();
      context.emit_token(TOKEN_EQ);
    } else {
      context.emit_token(TOKEN_ASSIGN);
    }
  } else if (next == u"<") {
    context.read_next_grapheme_cluster();
    if (context.are_more_grapheme_clusters() &&
        context.peek_next_grapheme_cluster() == u"<") {
      context.read_next_grapheme_cluster();
      if (context.are_more_grapheme_clusters() &&
          context.peek_next_grapheme_cluster() == u"=") {
        context.read_next_grapheme_cluster();
        context.emit_token(TOKEN_BIT_SHL_ASSIGN);
      } else {
        context.emit_token(TOKEN_BIT_SHL);
      }
    } else if (context.are_more_grapheme_clusters() &&
               context.peek_next_grapheme_cluster() == u"=") {
      context.read_next_grapheme_cluster();
      context.emit_token(TOKEN_LE);
    } else {
      context.emit_token(TOKEN_LT);
    }
  } else if (next == u">") {
    context.read_next_grapheme_cluster();
    if (context.are_more_grapheme_clusters() &&
        context.peek_next_grapheme_cluster() == u">") {
      context.read_next_grapheme_cluster();
      if (context.are_more_grapheme_clusters() &&
          context.peek_next_grapheme_cluster() == u"=") {
        context.read_next_grapheme_cluster();
        context.emit_token(TOKEN_BIT_SHR_ASSIGN);
      } else {
        context.emit_token(TOKEN_BIT_SHR);
      }
    } else if (context.are_more_grapheme_clusters() &&
               context.peek_next_grapheme_cluster() == u"=") {
      context.read_next_grapheme_cluster();
      context.emit_token(TOKEN_GE);
    } else {
      context.emit_token(TOKEN_GT);
    }
  } else if (next == u"(") {
    context.read_next_grapheme_cluster();
    context.emit_token(TOKEN_LPAREN);
  } else if (next == u")") {
    context.read_next_grapheme_cluster();
    context.emit_token(TOKEN_RPAREN);
  } else if (next == u"{") {
    context.read_next_grapheme_cluster();
    context.emit_token(TOKEN_LBRACE);
  } else if (next == u"}") {
    context.read_next_grapheme_cluster();
    context.emit_token(TOKEN_RBRACE);
  } else if (next == u",") {
    context.read_next_grapheme_cluster();
    context.emit_token(TOKEN_COMMA);
  } else if (next == u":") {
    context.read_next_grapheme_cluster();
    context.emit_token(TOKEN_COLON);
  } else if (next == u";") {
    context.read_next_grapheme_cluster();
    context.emit_token(TOKEN_SEMICOLON);
  } else if (next == u".") {
    context.read_next_grapheme_cluster();
    context.emit_token(TOKEN_DOT);
  } else if (next == u" " || next == u"\t" || next == u"\n") {
    context.read_next_grapheme_cluster();
    context.skip_token();
  } else if (next[0] >= u'0' && next[0] <= u'9') {
    context.read_next_grapheme_cluster();

    while (context.are_more_grapheme_clusters()) {
      next = context.peek_next_grapheme_cluster();

      LT_ASSERT(!next.empty(), "grapheme clusters cannot be empty");

      if (!((next[0] >= u'0' && next[0] <= u'9') ||
            (next[0] >= u'a' && next[0] <= u'z') ||
            (next[0] >= u'A' && next[0] <= u'Z') || next[0] == '.' ||
            next[0] == '_')) {
        break;
      }

      context.read_next_grapheme_cluster();
    }

    context.emit_token(TOKEN_LITERAL_NUMBER);
  } else if (lt::is_symbol_start(next)) {
    context.read_next_grapheme_cluster();

    while (context.are_more_grapheme_clusters()) {
      if (!lt::is_symbol_continue(context.peek_next_grapheme_cluster())) {
        break;
      }

      context.read_next_grapheme_cluster();
    }

    if (context.current_value() == u"as") {
      context.emit_token(TOKEN_KW_AS);
    } else if (context.current_value() == u"bool") {
      context.emit_token(TOKEN_KW_BOOL);
    } else if (context.current_value() == u"break") {
      context.emit_token(TOKEN_KW_BREAK);
    } else if (context.current_value() == u"const") {
      context.emit_token(TOKEN_KW_CONST);
    } else if (context.current_value() == u"continue") {
      context.emit_token(TOKEN_KW_CONTINUE);
    } else if (context.current_value() == u"do") {
      context.emit_token(TOKEN_KW_DO);
    } else if (context.current_value() == u"else") {
      context.emit_token(TOKEN_KW_ELSE);
    } else if (context.current_value() == u"explicit") {
      context.emit_token(TOKEN_KW_EXPLICIT);
    } else if (context.current_value() == u"f32") {
      context.emit_token(TOKEN_KW_F32);
    } else if (context.current_value() == u"f64") {
      context.emit_token(TOKEN_KW_F64);
    } else if (context.current_value() == u"false") {
      context.emit_token(TOKEN_KW_FALSE);
    } else if (context.current_value() == u"func") {
      context.emit_token(TOKEN_KW_FUNC);
    } else if (context.current_value() == u"i16") {
      context.emit_token(TOKEN_KW_I16);
    } else if (context.current_value() == u"i32") {
      context.emit_token(TOKEN_KW_I32);
    } else if (context.current_value() == u"i64") {
      context.emit_token(TOKEN_KW_I64);
    } else if (context.current_value() == u"i8") {
      context.emit_token(TOKEN_KW_I8);
    } else if (context.current_value() == u"if") {
      context.emit_token(TOKEN_KW_IF);
    } else if (context.current_value() == u"inherits") {
      context.emit_token(TOKEN_KW_INHERITS);
    } else if (context.current_value() == u"interface") {
      context.emit_token(TOKEN_KW_INTERFACE);
    } else if (context.current_value() == u"isize") {
      context.emit_token(TOKEN_KW_ISIZE);
    } else if (context.current_value() == u"let") {
      context.emit_token(TOKEN_KW_LET);
    } else if (context.current_value() == u"namespace") {
      context.emit_token(TOKEN_KW_NAMESPACE);
    } else if (context.current_value() == u"return") {
      context.emit_token(TOKEN_KW_RETURN);
    } else if (context.current_value() == u"self") {
      context.emit_token(TOKEN_KW_SELF);
    } else if (context.current_value() == u"struct") {
      context.emit_token(TOKEN_KW_STRUCT);
    } else if (context.current_value() == u"true") {
      context.emit_token(TOKEN_KW_TRUE);
    } else if (context.current_value() == u"type") {
      context.emit_token(TOKEN_KW_TYPE);
    } else if (context.current_value() == u"u16") {
      context.emit_token(TOKEN_KW_U16);
    } else if (context.current_value() == u"u32") {
      context.emit_token(TOKEN_KW_U32);
    } else if (context.current_value() == u"u64") {
      context.emit_token(TOKEN_KW_U64);
    } else if (context.current_value() == u"u8") {
      context.emit_token(TOKEN_KW_U8);
    } else if (context.current_value() == u"usize") {
      context.emit_token(TOKEN_KW_USIZE);
    } else if (context.current_value() == u"void") {
      context.emit_token(TOKEN_KW_VOID);
    } else if (context.current_value() == u"while") {
      context.emit_token(TOKEN_KW_WHILE);
    } else {
      context.emit_token(TOKEN_SYMBOL);
    }
  } else {
    emit_syntax_error_unexpected_character(context.message_context(),
                                           context.current_range());
    context.read_next_grapheme_cluster();
    context.skip_token();
  }
}
}  // namespace forge
