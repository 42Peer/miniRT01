

<파싱에서 예외처리>

type이 A C L sp pl cy 로만 되어있는지 검사

input 숫자가 유효한지 검사
	숫자가 맞는지 (char 이면 안됨) 
		-> atod에서 처리?
	콤마 갯수가 맞는지(3차원 좌표이면 콤마 두개) -> str_to_vec3 
		-> get_split_size() != 3 -> exit();
	color -> 0-255 range
		-> is_valid_rgbrange() 	
	ratio -> 0.0-1.0
		-> is_valid() 	
	벡터 -> != 0,0,0
		-> is_valid()
camera
	normalized oriented vector -> 0,0,0 이면 안됨

left_top 수정 필요
필수 파트 A, L, C 한 개만 있어야함
