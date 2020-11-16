//
// Created by Hugor Chau on 11/16/20.
//

#ifndef CAM_TYPES_H
# define CAM_TYPES_H

typedef struct		s_cam
{
	t_id			id;
	char			*name;
	t_tfm			transform;
	t_vec2			fov;
}					t_cam;

#endif //CAM_TYPES_H
