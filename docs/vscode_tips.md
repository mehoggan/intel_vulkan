# VS Code Markdown Preview Cheatsheet

| Action | Shortcut | What it does |
|---|---|---|
| Preview only | `Ctrl+Shift+V` | Replaces the text editor tab with rendered preview |
| Editor + Preview split | `Ctrl+K V` | Opens preview in a new pane beside the editor |
| Refresh preview | `Ctrl+K R` *(custom keybinding)* | Forces the preview to re-render from disk — use this when the preview shows stale content after an external edit |
| Back to raw text | Right-click tab → **Reopen Editor With...** → **Text Editor** | Undoes either of the above |

## Custom keybinding added

Added to `~/.config/Code/User/keybindings.json`:

```json
[
    {
        "key": "ctrl+k r",
        "command": "markdown.preview.refresh"
    }
]
```

Binds `Ctrl+K R` to **Markdown: Refresh Preview**, mirroring the existing `Ctrl+K V` (open preview to the side) mnemonic.

## Also set

`~/.config/Code/User/settings.json` has `.md` files opening directly in preview mode by default:

```json
"workbench.editorAssociations": {
    "*.md": "vscode.markdown.preview.editor"
}
```

Note: this only applies to tabs opened *after* the setting is saved — already-open tabs need to be closed and reopened to pick it up.
