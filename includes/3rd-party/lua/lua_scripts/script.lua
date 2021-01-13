 local mt = {
   __index =
      function(t, k)
         local inner = {}
         rawset(t, k, inner)
         return inner
      end
}
matrix = setmetatable({}, mt)
rigthKey = 0
upKey = 1
leftKey = 2
downKey = 3

mapDirection = 0


function insert_road_block(x, y)
  matrix[x][y] = true
end

function insert_bad_block(x, y)
  matrix[x][y] = false
end

math.randomseed(os.time())
