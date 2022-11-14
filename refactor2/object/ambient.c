
t_ambient ambient(t_scene *scene, char **data)
{
	t_ambient ambient;

	ambient.ambient = a_to_d(data[1]);
	ambient.color = parse_color(data[2]);
}
