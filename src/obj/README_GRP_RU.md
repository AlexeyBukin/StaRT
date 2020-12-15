## Группа (grp)
Группа в проекте StaRT представленa объектом типа `OBJ_GROUP`
содержащим структуру ниже:

```
typedef struct                 s_obj_group
{
	struct s_scn_object    **children;
	size_t                 child_num;
}                              t_obj_group;
```

Группа содержит массив ссылок на дочерние объекты.

Подробнее:
1) Об объектах можно узнать в `README_OBJ_RU.md`.
