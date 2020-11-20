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
3) material - defaul PBR material. See `scn_material.h`

#### `add sphere`
1) `-p` - position. Should be valid vector
2) `-r` - radius. Should be valid scalar
1) `-m` - set material. May be name string or id integer.

#### `add plane`
1) `-n` - normal vector. Should be valid vector
2) `-d` - distance from plane to origin. Should be valid scalar
1) `-m` - set material. May be name string or id integer.

#### `add cylinder`
1) `-p` - position. Should be valid vector
2) `-c` - cap. Should be valid vector
3) `-r` - radius. Should be valid scalar
1) `-m` - set material. May be name string or id integer.

#### `add cone`
1) `-p` - position. Should be valid vector
2) `-c` - cap. Should be valid vector
3) `-r` - radius. Should be valid scalar
1) `-m` - set material. May be name string or id integer.

#### `add material`
1) `-m` - metalness. Should be valid vector
2) `-r` - roughness. Should be be valid vector
3) `-o` - ior. Should be valid scalar
3) `-t` - transparency. Should be valid scalar
3) `-a` - albedo. Should be valid vector (values clamped 0..1)
3) `-f` - f0. Should be valid vector (values clamped 0..1)

#### `add camera`
1) `-p` - position. Should be valid vector
2) `-f` - forward-vector. Should be be valid vector
3) `-u` - up-vector. Should be valid vector
4) `-v` - field-of-view, FOV. Should be valid scalar

### `rm`
Removes component from scene
1) `-i` - remove component by index
1) `-n` - remove component by name

### `set`
Sets property value to component

Uses flags from `add` to specify parameters 
1) `-i` - choose component by index
1) `-n` - choose component by name

### `ls`
Lists chosen component info

If no flag/argument specified then it lists info about scene
1) `-i` - choose component by index
1) `-n` - choose component by name

## Comments
You can comment only full line by starting it with `#`

## Examples
```
# This is comment

# Adding default material
add material pbr "my_material"

#Adding sphere to the origin with default material, index 8 and radius 3 named my_sphere
add object sphere -i8 -m"my_material" -r3.0 "my_sphere"

#add works like this
add object sphere "my_sphere" -p<0, 0, 0>

#set works like this
set object sphere "my_sphere" -p<0, 0, 0>
```

P.S.

В течении add и set комманд мы пытаемся провернуть операцию с временным объектом
Если в течении парсинга происходят ошибки просто очищаем временный объект
Иначе копируем временный объект в постоянное хранилище