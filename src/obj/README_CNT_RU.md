## Контейнер (cnt)
Контейнер в проекте StaRT представлен объектом типа `OBJ_CONTAINER`
содержащим структуру ниже:

```
typedef struct        s_obj_container
{
	t_shp_type    shape_type;
	t_shp         shape;
	t_mat         *material;
}                     t_obj_container;
```

Контейнер содержит описание фигуры и ссылку на материал.

Подробнее:
1) Об объектах можно узнать в `README_OBJ_RU.md`.
2) О материалах можно узнать в `README_MAT_RU.md`.
