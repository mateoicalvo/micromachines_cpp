local function go_back_way(radians, exdirection)
	distance = math.abs(exdirection - radians)
	if distance < math.pi then
		if exdirection > radians then
			return leftKey
		else
			return rightKey
		end
	else
		if exdirection > radians then
			return rigthKey
		else
			return leftKey
		end
	end
end

local function  get_direction(radians)
	local cos = math.cos(radians)
	local sin = math.sin(radians)
	local i = 0
	local j = 0
	
	if cos > 0 then
		i = -1
	elseif cos < 0 then
		i = 1
	end
	
	if sin > 0 then
		j = -1
	elseif sin < 0 then
		j = 1
	end
	return i, j	
end


local function get_nearest_block(x, y)
	local nearest_block = 1000
	local nearest_block_x = 0
	local nearest_block_y = 0

	for i = 0, 1, #matrix do
		for j = 0, 1, #matrix[i] do 
			if (matrix[i][j]) then
				local a = x - i
				local b = y - j
				local distance = math.sqrt(math.pow(a, a) + math.pow(b, b))
				if distance < nearest_block then
					nearest_block = distance
					nearest_block_x = i
					nearest_block_y = j
				end
			end
		end
	end
	return nearest_block_x, nearest_block_y
end


local function exists_block_going(x, y, radians)
	local i, j = get_direction(radians)
	return matrix[x + i][y + j] or matrix[x + i][y] or matrix[x][y + j]
end


local function get_angle_to_block(x, y, w, z)
	return math.atan2(z - y, w - x)
end

local function curve_coming(x, y, radians)
  	local left_right, up_down = get_direction(radians)
  	if matrix[x + (left_right * 3)][y + (up_down*3)] then
  		return true
  	end
  	return false
end

local function return_to_road(x, y, radians)
	local near_x, near_y = get_nearest_block(x, y)
	local new_angle = get_angle_to_block(x, y, near_x, near_y)
	return go_back_way(radians, new_angle)
end

local function ret()
	return upKey
end

function get_instruction(x, y, angle)
	local instructions = {}
	instructions[0] = upKey
	instructions[1] = upKey
	instructions[2] = downKey
	instructions [3] = downKey
	if instructions [ math.random(0,  #instructions - 1) ] == upKey then
		return upKey
	end

	if (angle - 360) <= 0 then
		angle = angle - 360
	end
	angle = angle * -1
	angle = (90 + angle) % 360
	local radians = math.rad(angle)
	


	if not matrix[x][y] then
		return return_to_road(x, y, radians) 
	end
	if exists_block_going(x, y, radians) then
		mapDirection = radians
		if curve_coming(x, y, radians) then
			return leftKey
		end
		return upKey
	end
	return go_back_way(radians, mapDirection)
end


