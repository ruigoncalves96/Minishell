*This project has been created as part of the 42 curriculum by hguerrei and randrade*

# Minishell

*Rank 03 — writing a shell.*

## Description

Minishell is a working reimplementation of a subset of `bash`. It shows a prompt, keeps
a history, and executes what you type: builtins, binaries found on `PATH`, pipelines,
redirections, heredocs, environment-variable expansion, and the exit status of the last
command. It is the largest project of the Common Core so far, and the first done in a
pair.

The interesting part is that a shell is really two programs stacked on each other. The
front half is a **language problem**: a line of text has to be split into tokens,
checked for syntax, expanded, stripped of quotes, and shaped into a structure that
describes what to run. The back half is a **systems problem**: `fork`, `execve`, `pipe`,
`dup2`, `waitpid`, and getting file descriptors closed in every one of them so the
pipeline neither hangs nor leaks.

Quoting is where the two halves meet and where most of the difficulty lives. `'$HOME'`
is literal, `"$HOME"` expands, and `$HOME` expands and then splits — so quote removal
cannot happen before expansion, and expansion cannot happen before you know which quotes
each character was inside.

## Instructions

### Prerequisites

- `cc`, `make`
- **GNU readline.** Not libedit — the project calls `rl_clear_history`, which the
  libedit shim shipped with macOS does not provide. See [Platform](#platform).

### Build

```sh
make
```

### Makefile targets

| Target           | Effect                                                        |
|------------------|---------------------------------------------------------------|
| `make`           | Build `libft.a`, then `minishell` (same as `all`)              |
| `make valgrind`  | Run under Valgrind with `readline.supp` and `--track-fds=yes`  |
| `make clean`     | Remove the object directory                                    |
| `make fclean`    | `clean` + remove the binary and `libft.a`                      |
| `make re`        | `fclean` then `all`                                            |

`readline.supp` suppresses the allocations GNU readline never frees, so the Valgrind
output shows only leaks that belong to this project.

### Platform

The Makefile targets Linux, where `-lreadline` is GNU readline. macOS resolves
`-lreadline` to the libedit compatibility shim, which lacks `rl_clear_history` and fails
to compile. With Homebrew's readline installed it builds and runs:

```sh
make FLAGS="-Wall -Werror -Wextra -I/opt/homebrew/opt/readline/include" \
     READLINE="-L/opt/homebrew/opt/readline/lib -lreadline"
```

The commented `-L/opt/homebrew/opt/readline` already in the Makefile is a remnant of the
same workaround.

### Usage

```sh
./minishell
```

```
Minishell> echo "home is $HOME" | tr a-z A-Z
HOME IS /USERS/RUIGONCALVES
Minishell> ls nonexistent; echo $?
```

`ctrl-C` redraws a fresh prompt, `ctrl-D` exits, `ctrl-\` does nothing — as in bash.

## Features

### Builtins

| Builtin | Support |
|---------|---------|
| `echo` | with `-n` |
| `cd` | relative and absolute paths |
| `pwd` | no options |
| `export` | no options; also lists export-only variables |
| `unset` | no options |
| `env` | no options or arguments |
| `exit` | with an optional numeric status |

### Shell features

| Feature | Notes |
|---------|-------|
| `\|` pipes | arbitrary length pipelines |
| `<` `>` `>>` | input, output, append |
| `<<` heredoc | reads until the delimiter; does not touch history |
| `'single quotes'` | fully literal |
| `"double quotes"` | literal except `$` |
| `$VAR` | environment expansion |
| `$?` | exit status of the last foreground pipeline |
| history | via readline's `add_history` |
| signals | `ctrl-C`, `ctrl-D`, `ctrl-\` |

The bonus (`&&`, `||`, parentheses, wildcards) was not attempted.

## Verified behaviour

Exercised against the built binary:

| Input | Result |
|-------|--------|
| `echo hello world` | `hello world` |
| `echo -n no-newline` | no trailing newline |
| `/bin/echo absolute path` | runs via absolute path |
| `ls Makefile` | found on `PATH` |
| `echo $HOME` | expands |
| `echo "quoted $HOME"` | expands inside double quotes |
| `echo 'literal $HOME'` | stays literal |
| `echo a \| cat \| cat` | `a` — three-stage pipeline |
| `echo x > f`, `cat < f`, `echo y >> f` | all three redirections |
| `export FOO=bar`, `echo $FOO` | `bar` |
| `unset FOO`, `echo [$FOO]` | `[]` |
| `true`, `echo $?` | `0` |
| `nosuchcmd`, `echo $?` | `127` |

Error paths, all on stderr with bash-accurate wording:

| Input | stderr | exit |
|-------|--------|------|
| `nosuchcmd_xyz` | `nosuchcmd_xyz: command not found` | 127 |
| `echo "unclosed` | `syntax error unclosed quote` | — |
| `\| echo x` | ``minishell: syntax error near unexpected token `\|'`` | — |
| `echo a >` | ``minishell: syntax error near unexpected token `newline'`` | — |
| `cat < /nope/missing` | `minishell: /nope/missing: No such file or directory` | — |
| `exit abc` | `minishell: exit: abc: numeric argument required` | 2 |
| `exit 999` | — | 231 (`999 % 256`) |

## Architecture

A line travels through the parser in a fixed order, in `parsing()`:

```
readline()
  └─ build_tokens_list()   split the raw line into a doubly linked list of tokens
  └─ parse_syntax()        reject unclosed quotes and misplaced operators
  └─ expand_vars()         substitute $VAR and $?, respecting quote context
  └─ convert_quotes()      remove the quotes themselves, now that expansion is done
  └─ define_tokens()       group the flat list into commands with their redirections
  └─ loop_and_open_fd()    open redirection targets, collect heredoc input
  └─ build_tree()          link the commands into the pipeline the executer walks
```

Then `loop_executer()` forks a process per command, wires the pipes with `dup2`, applies
each command's redirections, and `execve`s — running builtins in the parent when they
must affect shell state.

Two list types carry the line: `t_list` is the flat token stream during parsing (`str`,
`type`, `subtype`, both links), and `t_token` is the grouped command produced afterwards
(`char **token` argv, a `t_redirect`, and links).

## Project structure

```
Minishell/
├── Makefile
├── readline.supp          # Valgrind suppressions for readline's own allocations
├── includes/minishell.h   # every struct, error string, and token constant
├── src/
│   ├── main.c             # prompt loop, EOF and ctrl-C handling
│   ├── parsing/           # 15 files: tokenising, syntax, expansion, quotes, heredoc
│   ├── executer/          # 9 files: fork/execve, pipes, redirections, PATH, signals
│   ├── builtins/          # 14 files: the seven builtins plus env/export management
│   └── utils/             # 10 files: struct helpers, cleanup, error handling
└── Library/               # libft + ft_printf + get_next_line
```

Roughly, parsing was mine and the builtins were Hugo's, with the executer shared — though
174 commits across five branches blurred that considerably.

## Implementation notes

- **Expansion happens before quote removal, and that ordering is load-bearing.** Each
  token records the quote context it was found in, so `expand_vars` knows whether a `$`
  is live or inert. Only afterwards does `convert_quotes` strip the quote characters. Do
  it the other way round and `'$HOME'` and `"$HOME"` become indistinguishable.
- **The token list is doubly linked.** Syntax checking constantly asks about the
  *previous* token — an operator at the start of a line is an error, two operators in a
  row is an error, a redirection needs a word after it — and a `previous` pointer makes
  those checks local instead of requiring lookahead state.
- **Redirections hang off the command, not the token stream.** By the time the executer
  runs, each `t_token` carries a `t_redirect` with an already-open `fd`. Opening files
  during parsing means a failure like `cat < /nope/missing` is reported before anything
  forks.
- **One global, as the subject demands.** `g_heredoc_c_pressed` is a
  `volatile sig_atomic_t` and holds nothing but a flag. The subject forbids a global
  that reaches shell state, so the handler sets this and the main loop turns it into
  exit code 130.
- **`export` tracks variables that are not in `env`.** A bare `export FOO` marks a
  variable as declared-but-unset; `is_export_only` records that, so `export` lists it
  while `env` does not — matching bash.
- **`exit` truncates like bash.** `exit 999` yields 231, because the status is taken
  modulo 256; a non-numeric argument gives 2 and the `numeric argument required`
  message.
- **Cleanup is centralised.** `cleanup_all` plus `close_fds` run on every exit path, so
  a failure deep in the executer still releases the environment list, the token tree,
  and any descriptors that were opened for redirections.

### Known limitations

- **Does not build on macOS as configured** — see [Platform](#platform). The flags need
  overriding to point at GNU readline.
- **Some near-duplicate struct fields survive.** `t_token` carries both `prev` and
  `previous`; only one is meaningful.
- **No bonus part.** `&&`, `||`, parentheses, and wildcard expansion were not attempted.

## Resources

- `man 3 readline`, `man 2 execve`, `man 2 pipe`, `man 2 dup2`, `man 2 waitpid`
- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html) — the behaviour being matched
- [`minishell.pdf`](../../../../Subjects/Rank_3/minishell.pdf) — the project subject
- [Libft](../../Rank_0/Libft), [ft_printf](../../Rank_1/ft_printf), [get_next_line](../../Rank_1/get_next_line) — bundled in `Library/`
