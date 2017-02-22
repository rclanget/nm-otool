#include "otool.h"

int64_t		ft_swap_64(t_struct *s, int64_t i)
{
	if (s->swap)
	{
		return (((i >> 0x38) & 0x00000000000000ffLL)
			| ((i >> 0x28) & 0x000000000000ff00LL)
			| ((i >> 0x18) & 0x0000000000ff0000LL)
			| ((i >> 0x08) & 0x00000000ff000000LL)
			| ((i << 0x08) & 0x000000ff00000000LL)
			| ((i << 0x18) & 0x0000ff0000000000LL)
			| ((i << 0x28) & 0x00ff000000000000LL)
			| ((i << 0x38) & 0xff00000000000000LL));
	}
	return (i);
}

uint32_t	ft_swap_32(t_struct *s, uint32_t val)
{
	if (s->swap)
	{
		val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
		return (val << 16) | (val >> 16);
	}
	return (val);
}