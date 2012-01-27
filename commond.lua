function getFrame(fun)
   local func = coroutine.create(fun)
   return function ()
	     local state = coroutine.resume(func)
	     return state
	  end
end

function Suspend()
   while true do
      coroutine.yield()
   end
end

function WaitFrame(ti)
   for i = 1, ti do 
      coroutine.yield()
   end
end



LocationFunc.circle = function (r, x, y, det)
		   local angle = 0 
		   local dx
		   local dy

		   return function (cmd)
			     if cmd == 'updata' then
				dx = math.sin(angle)*r
				dy = math.cos(angle)*r
				angle = angle + det
				return { x = x + dx, y = y + dy }
			     else 
				return { x = x, y = y }
			     end
			  end
		end

LocationFunc.stable = function (x, y)
			 return function (cmd)
				   return { x = x, y = y }
				end
		      end

ClipFunc.stable = function (x, y, w, h)
		     return function (cmd)
			       return { x = x, y = y, w = w, h = h }
			    end
		  end


ClipFunc.move = function (x, y, w, h, dx, dy)
		   return function (cmd)
			     if cmd == 'updata' then
				x = x + dx
				y = y + dy
				return { x = x, y = y, w = w, h = h }
			     else
				return { x = x, y = y, w = w, h = h }
			     end
			  end
		end



RangeCheckFunc.retangle = function (ux, uy, w, h)
			     return function (x, y)
				       return ux <= x and x < ux+w and uy <= y and y < uy + h
				    end
			  end


SceneFunc.GetNextFrameTime = function (t, last_ti)
				local cur = -1
				local ti
				for k, v in pairs(t) do
				   if type(k) == 'string' and k ~= 'data' then
				      ti = SceneFunc.GetNextFrameTime(t[k], last_ti)
				      if ti >= 0 and (cur == -1 or ti < cur) then					 
					 cur = ti;
				      end
				   end
				end
				
				if type(t['data']) == 'table' and type(t['data']['frame_event']) == 'function' then
				   ti = t['data']['frame_event'](last_ti)
				   if ti >= 0 and (cur == -1 or ti < cur) then
				      cur = ti;
				   end
				end

				if cur == -1 then cur = 1000 end
				return cur
			     end


TimerFunc.FrameTimer = function (interval)
			  local current = interval
			  return function (ti)
				    current = current - ti
				    if current <= 0 then current = interval end
				    return current
				 end
		       end

TimerFunc.ScriptEvent = function (self, ti)
			   self.resetScriptEvent(ti)
			   WaitFrame(1)
			end



TextFunc.text = function (self, text)
		   self:sendtext(text)
		   WaitFrame(1)
		end