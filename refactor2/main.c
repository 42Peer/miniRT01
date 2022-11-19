#include "./include/minirt.h"

char ***junkpark;
char ***mher;
char ***yubchoi;
char ***ppm_file;


int	main(int argc, char **argv)
{
	t_scene	scene;
	junkpark = get_ppm_file("./assets/junkpark120_120.pbm");
	mher = get_ppm_file("./assets/mher120_120.pbm");
	yubchoi = get_ppm_file("./assets/yubchoi120_120.pbm");
	if (argc != 2)
		exit_with_error("Wrong number of arguments\n");
	scene = parse(argv[1]);
	set_mlx(&scene.mlx);
	pixel_put(&scene, ppm_file);
	mlx_put_image_to_window(scene.mlx.mlx, scene.mlx.win, scene.mlx.img, 0, 0);
	mlx_loop(scene.mlx.mlx);
}
