function getFrame(fun)
   local func = coroutine.create(fun)
   return function ()
	     state = coroutine.resume(func)
	     return state
	  end
end

function Suspend()
   while true do
      print('here')
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

		   return function ()
			     dx = math.sin(angle)*r
			     dy = math.cos(angle)*r
			     angle = angle + det
			     return {x = x + dx, y = y + dy}
			  end
		end

LocationFunc.none = function ()
		 return nil
	      end



ClipFunc.move = function (x, y, w, h, dx, dy)
		   return function ()
			     x = x + dx
			     y = y + dy
			     return { x = x, y = y, w = w, h = h }
			  end
		end



RangeCheckFunc.retangle = function (ux, uy, w, h)
			     return function (x, y)
				       return ux <= x and x < ux+w and uy <= y and y < uy + h
				    end
			  end


SceneFunc.GetNextFrameTime = function (t, last_ti)
				cur = -1
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

				if cur == -1 then cur = 100 end
				return cur
			     end


TimerFunc.FrameTimer = function (interval)
			  current = interval
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