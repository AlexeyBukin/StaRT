# Parsing manual

## List of main commands
1) `add` - adds component to scene
2) `rm` - removes component from scene
3) `set` - sets some parameter given value
3) `ls` - lists info about scene/object

### `add`
1) `-t` - type parameter. May be one of `sphere`, `cone`, `cylinder`, `plane` and `material`
1) `-m` - material parameter. Should be valid material `id`, works with objects only
1) `-i` - set `id`
1) `-n` - set `name`

In case some additional parameters are not specified, they would be set to default values.

#### `add sphere`
1) `-p` - position. Should be in form `<n.m, n.m, n.m>`
2) `-r` - radius. Should be valid float

#### `add plane`
1) `-n` - normal vector. Should be in form `<n.m, n.m, n.m>`
2) `-d` - distance from plane to origin. Should be valid float

#### `add cylinder`
1) `-p` - position. Should be in form `<n.m, n.m, n.m>`
2) `-c` - cap. Should be in form `<n.m, n.m, n.m>`
3) `-r` - radius. Should be valid float

#### `add cone`
1) `-p` - position. Should be in form `<n.m, n.m, n.m>`
2) `-c` - cap. Should be in form `<n.m, n.m, n.m>`
3) `-r` - radius. Should be valid float

### `rm`
1) `-i` - remove object by index
1) `-n` - remove object by name

### `set`
1) `-i` - choose object by index
1) `-n` - choose object by name

`set` uses flags from `add` to specify parameters 
