# Parsing manual

## List of main commands
1) `add` - adds component to scene
2) `rm` - removes component from scene
3) `set` - sets some parameter given value
3) `ls` - lists info about scene/object

### `add`
1) `-t` - type parameter. May be one of `sphere`, `cone`, `cylinder` and `plane`
1) `-m` - material parameter. Should be valid material `id`

#### `add sphere`
1) `-p` - position of object. Should be in form `<n.m, n.m, n.m>`

### `rm`
1) `-i` - remove object by index
1) `-n` - remove object by name
