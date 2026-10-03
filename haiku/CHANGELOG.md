# Terminology for Haiku: changelog

One entry per published package revision (version 1.14.0), newest first. The
tag of a revision is `haiku-1.14.0-<revision>`, and the link next to it lists
the code that changed since the revision before. The recipe is
`terminology-1.14.0.recipe` in this directory. The package needs the `efl`
package of the revision named in each entry (or a newer one).

Revision 1 was an early build, and revision 3 a test build, that were never
published.

## Known issues

* `--nebula` uses OpenGL with the Nebula NVIDIA driver, and with that driver
  the window freezes and ending the program can hang the system. The fault is
  in the driver, not in Terminology. Without `--gl` or `--nebula` Terminology
  does not use OpenGL.
* paths dropped on the window are pasted as they are: paths with spaces in them
  are not quoted.
* dragging links or text out of the window is not implemented.

## Revision 8 (2026-10-03)

Tag `haiku-1.14.0-8`, source `bf86d98`. Needs `efl` revision 11.
[Changes since revision 7](https://github.com/ablyssx74/terminology/compare/haiku-1.14.0-7...haiku-1.14.0-8)

* Ctrl+C and other typed keys reach a program that floods the terminal (`yes`,
  `cat` of a big file). On Haiku they used to wait for the flood to end, and
  input that could not be written at once was thrown away.
* showing a binary file (`cat` of an executable) no longer keeps the terminal
  busy for minutes: the bell rings at most ten times a second.

## Revision 7 (2026-10-03)

Tag `haiku-1.14.0-7`, source `1e8c71a`. Needs `efl` revision 10.
[Changes since revision 6](https://github.com/ablyssx74/terminology/compare/haiku-1.14.0-6...haiku-1.14.0-7)

* dropping several files on the window pastes their paths separated by a space.
  They used to run together without anything between them, on every platform.
* with `efl` revision 10, files dropped from Tracker are pasted as paths, media
  files open as before, and text dragged from other applications is pasted.

## Revision 6 (2026-10-02)

Tag `haiku-1.14.0-6`, source `a6bf60a`. Needs `efl` revision 9.
[Changes since revision 5](https://github.com/ablyssx74/terminology/compare/haiku-1.14.0-5...haiku-1.14.0-6)

* `--gl` asks for OpenGL (the SDL engine) for a run, where the system allows it.
* `--nebula` is the opt-in with the Nebula NVIDIA driver: it allows OpenGL there
  and asks for it. Both settings are inherited by everything the terminal
  starts, so `elementary_config` started from the Toolkit settings sees them
  too.
* without either option Terminology does not use OpenGL, as before.

## Revision 5 (2026-09-30)

Tag `haiku-1.14.0-5`, source `2b66c34`. Needs `efl` revision 7.
[Changes since revision 4](https://github.com/ablyssx74/terminology/compare/haiku-1.14.0-4...haiku-1.14.0-5)

* clicking a URL, a file or an e-mail address works. Haiku has neither
  `xdg-open` nor `xdg-email`, so links are opened with the `open` command, which
  starts the handler of the type or scheme. Addresses are passed as `mailto:`
  URIs. A saved configuration that still names `xdg-open` or `xdg-email` is
  switched to `open` when it is loaded.
* needs `efl` revision 7, which fixes a freeze when clicking into the text
  fields of the mouse settings.

## Revision 4 (2026-09-30)

Tag `haiku-1.14.0-4`, source `edc9dee`. Needs `efl` revision 5.
[Changes since revision 2](https://github.com/ablyssx74/terminology/compare/haiku-1.14.0-2...haiku-1.14.0-4)

* the application is `/boot/system/apps/Terminology`. The `terminology` command
  and the Deskbar entry are links to it.
* the translucency check box and the opacity slider in the background settings
  are disabled, since Haiku windows have no alpha channel. Stored values are
  left alone.
* with `efl` revision 5 it uses the native Haiku window engine, without OpenGL.

## Revision 2 (2026-09-29)

Tag `haiku-1.14.0-2`, source `eb724fd`. First published revision.

* the haikuporter recipe, a vector icon and the application resources.
* pictures, videos and music can be shown inline (`tycat`, `typop`, `tyls`).
* to show the current directory in the window title, add this to
  `~/config/settings/bashrc`:

      case "$TERM" in
        xterm*|terminology*)
          PROMPT_COMMAND='printf "\033]0;Terminology - %s\007" "$PWD"'
          ;;
      esac
