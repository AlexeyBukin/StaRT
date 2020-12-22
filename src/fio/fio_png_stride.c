//
// Created by Hugor Chau on 12/22/20.
//

#include "rt.h"

int		fio_png_stride(int width)
{
	return (256 * (width / 256 +
		(width % 256 >= 1 ? 1 : 0)));
}
