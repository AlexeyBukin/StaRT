## Текстура (txr)

Текстура имеет уникальные ID и имя.
Структура содержит информацию о текстуре - 
размер, тип, выравнивание и ссылку на массив пикселей.

```
typedef struct  s_texture
{
    t_id        id;
    char        *name;
    t_txr_type  type;
    size_t      w;
    size_t      h;
    size_t      stride;
    char        *content;
}               t_txr;
```

Подробнее:
1) О сцене можно узнать в `README_SCN_RU.md`.
