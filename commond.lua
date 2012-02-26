LocationFunc = {}
ClipFunc = {}
RangeCheckFunc = {}
SceneFunc = {}
TimerFunc = {}
TextFunc = {}

local coroutine = coroutine

function subRoutine(fun)
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
				   if cmd == 'update' then
				      angle = angle + det
				   end
				   dx = math.sin(angle)*r
				   dy = math.cos(angle)*r
				   
				   return { x = x + dx, y = y + dy }
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
			     if cmd == 'update' then
				x = x + dx
				y = y + dy
			     end
			     return { x = x, y = y, w = w, h = h }
			  end
		end



RangeCheckFunc.retangle = function (ux, uy, w, h)
			     return function (x, y)
				       return ux <= x and x < ux+w and uy <= y and y < uy + h
				    end
			  end

TimerFunc.FrameTimer = function (interval)
			  local current = interval
			  return function (ti, cmd)
				    if cmd == 'update' then
				       current = current - ti
				       if current <= 0 then 
					  current = interval 
				       end
				    end
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