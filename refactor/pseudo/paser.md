
void	공백 스플릿(char *line)
{
	char **line_list = malloc();

	스플릿 문자(',') 두개 중복 체크?
	while (line_list)
	{
		*line_list = split(line);
		스플릿 개수 체크?
	}
}

void *wrap_malloc(size_t)
{
    void * ret;
    ret = malloc(size_t);
    if (!ret)
        exit(1);
    return (ret);
}

pl 0,1.2.,9...p 

스플릿에러(스플릿 개수 체크) 

플래그?
double	a_to_d()
{
	
}

t_color3 parse_color(char *s)
{
	t_color3 rgb;
	char	**tmp;

	tmp = split(s); // 컴마
	rgb.x = ft_atoi(tmp[0]);
	rgb.y = ft_atoi(tmp[1]);
	rgb.z = ft_atoi(tmp[2]);
	free_tmp
	return(rgb);
}


t_ambient create_ambient(char **data, )
{
	t_ambient ambient;

	ambient.ambient = a_to_d(data[1]);
	ambient.color = parse_color(data[2]);
}

void object_parser(char **line, t_scene *scene)
{
	char **data;
	while (line)
	{
		data = ft_split(line, ' ');
		line++;
	

		if (ft_strcmp(data[0], "A"))
			scene->ambient = create_ambient(data);
		else if (ft_strcmp(data[0], "L"))
			
		else if (ft_strcmp(data[0], "C"))

		else if (ft_strcmp(data[0], "pl"))

		else if (ft_strcmp(data[0], "sp"))

		else if (ft_strcmp(data[0], "cy"))

		else
			에러처리(); -> exit();
		free_data(...);
	}
}

char **file_parser(char *filename)
{
    t_scene scene;
	int fd;
	int count;
	char *raw_data;
	char **line;
	
	// .rt 체크
	fd = open(filename, 'r');
	while(!read)
		count += read(fd, 1byte);
	close(fd);

	fd = open(filename, 'r');
	raw_data = (char *)malloc(sizeof(char) * (count + 1));
	read(fd, raw_data, count);
	close(fd);
	line = ft_split(raw_data, '\n');
    return (line);
}

t_scene parser(char *filename)
{
	t_scene scene;
	char **line;

	line = file_parser(filename);
	object_parser(line, &scene);
	return (scene);
}

main()
{
	t_scene scene;
	...
	fd = open();
	scene = parser(av[1]);
	...
}