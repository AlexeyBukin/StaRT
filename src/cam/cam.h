//
// Created by Hugor Chau on 11/16/20.
//

#ifndef CAM_H
#define CAM_H

#include "cam_types.h"

int		cam_init(t_cam **cam, t_scn *scn, char *name);
int		cam_init_default(t_cam **dest, t_scn *scn);
int		cam_deinit(t_cam *cam);

#endif //CAM_H
