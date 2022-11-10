#include "mlx/mlx.h"

typedef struct  s_data
{
	void	*img;
	char	*addr;
	int	bits_per_pixel;
	int	line_length;
	int	endian;
}               t_data;

typedef struct  s_mlx
{
	void	*mlx;
	void	*win;
}               t_mlx;

void  my_mlx_pixel_put(t_data *data, int x, int y, int color);
int	key_hooking(int keycode, t_mlx *mlx);
