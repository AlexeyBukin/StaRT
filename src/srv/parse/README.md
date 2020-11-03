# Parsing manual

## List of main commands
1) `add` - adds component to scene
2) `rm` - removes component from scene
3) `set` - sets some parameter given value
3) `ls` - lists info about scene/object

### `add`
Main argument should be from list of `sphere`, `cone`, `cylinder`, `plane`, `camera` or `material`

#### Default values
In case some additional parameters are not specified, they would be set to this default values:
1) scalar - `0.0`
1) vector - `<0.0, 0.0, 0.0>`
1) string - empty string, `""`
2) id - next available id
3) material - defaul PBR material. See `scn_material.h`

#### `add <object_name>`
General instruction for objects commands:
1) `-i` - set `id`
1) `-m` - material parameter. Should be valid material `id`, works with objects only
Main argument represents object name. Should be valid string

#### `add sphere`
1) `-p` - position. Should be valid vector
2) `-r` - radius. Should be valid scalar

#### `add plane`
1) `-n` - normal vector. Should be valid vector
2) `-d` - distance from plane to origin. Should be valid scalar

#### `add cylinder`
1) `-p` - position. Should be valid vector
2) `-c` - cap. Should be valid vector
3) `-r` - radius. Should be valid scalar

#### `add cone`
1) `-p` - position. Should be valid vector
2) `-c` - cap. Should be valid vector
3) `-r` - radius. Should be valid scalar

#### `add material`
1) `-m` - metalness. Should be valid vector
2) `-r` - roughness. Should be be valid vector
3) `-o` - ior. Should be valid scalar
3) `-t` - transparency. Should be valid scalar
3) `-a` - albedo. Should be valid vector (values clamped 0..1)
3) `-f` - f0. Should be valid vector (values clamped 0..1)

#### `add camera`
1) `-m` - metalness. Should be valid vector
2) `-r` - roughness. Should be be valid vector
3) `-o` - ior. Should be valid scalar
3) `-t` - transparency. Should be valid scalar
3) `-a` - albedo. Should be valid vector (values clamped 0..1)
3) `-f` - f0. Should be valid vector (values clamped 0..1)

### `rm`
1) `-i` - remove component by index
1) `-n` - remove component by name

### `set`
1) `-i` - choose component by index
1) `-n` - choose component by name

`set` uses flags from `add` to specify parameters 
