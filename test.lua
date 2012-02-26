local Scene = SceneManager.create() --每个scene均设metatable的__index，所有的类函数放__index

local function test_chapter()

   Scene:insert('bg',
		{
		   data = {
		      attribute = 'sprite',
		      location = LocationFunc.stable(0, 0), 
		      clip = ClipFunc.move(1000, 0, 800, 600, -0.5, 0),
		      img = 'data/yama.bmp',
--		      frame_event = TimerFunc.FrameTimer(200)
		   }
		}
	     )
   
   Scene.bg:insert('hima', --data中每项以table, function 或 string 的形式出现
                {
		   data = {
		      attribute = 'sprite',
		      clip = ClipFunc.move(1000, 0, 800, 600, -1, 0),
		      location = LocationFunc.stable(0, 0),
		      img = 'data/hima.png',
		      frame_event = TimerFunc.FrameTimer(100)
		   }
		}
	     )

   Scene.bg.hima:insert('mori',
		     {
			data = {
			   attribute = 'sprite', 
			   clip = ClipFunc.stable(0, 0, 336, 735),
			   location = LocationFunc.circle(5, 400, 5, 0.2),
			   img = 'data/mori.png',
			   frame_event = TimerFunc.FrameTimer(100)
			}
		     }
		  )

   Scene.bg.hima.mori:insert('maintext',
   			     {
   				data = { 
   				   attribute = 'textbox',
   				   clip = ClipFunc.stable(0, 0, 800, 100),
   				   location = LocationFunc.stable(0, 200),
   				   frame_event = TimerFunc.FrameTimer(100),
				   
   				   OnMouseRange = RangeCheckFunc.retangle(0, 0, 800, 600),
				   
   				   wordlayer = {
   				      font_name = 'data/simhei.ttf',
   				      font_size = 20,
				      box = { width = 800, height = 100, color = 0xa0000000 },
--   				      box = 'data/w_win.bmp', -- img = { width = 0, height = 0, color = 0 } 前者直接用图片，后者自制对话框
   				      x = 5,
   				      y = 10,
   				      width = 780,
   				      height = 200,
   				      text_color = 0xffffffff,
   				   }
   				}
   			     }
   			  )

   Scene.bg.hima.mori.maintext:text('先来个自我介绍吧')

   Scene.bg.hima.mori.maintext:text('我是森田贤一 ')

   Scene.bg.hima.mori.maintext:text('最喜欢的就是科幻小说跟大姐姐 ')
   
   Scene.bg.hima.mori.maintext:text('我常看的一本书中有一个名为『日本』的国家 ')
   
   Scene.bg.hima.mori.maintext:text('你或许也已经知道了，这是一个会让人产生浓厚兴趣的奇妙岛国 ')
   
   Scene.bg.hima.mori.maintext:text('你问什么地方有意思？ ')
   
   Scene.bg.hima.mori.maintext:text('比如说在现实里，要是杀了人不是就要背负『一生不得拥有小孩的义务』吗？ ')
   
   Scene.bg.hima.mori.maintext:text('之后就会受到一群叫『特别高等人』的恐怖家伙的保护观察 ')
   
   Scene.bg.hima.mori.maintext:text('不过『日本』并不同 ')
   
   Scene.bg.hima.mori.maintext:text('杀人是要被以绞刑处死的 ')
   
   Scene.bg.hima.mori.maintext:text('又或是会被关进一个叫刑务所的地方十几二十年的，可能是一辈子也不一定 ')
   
   Scene.bg.hima.mori.maintext:text('刑务所好像又称牢房或是监狱，我们的国家里并不存在这种设施，所以挺有意思的 ')
   
   Scene.bg.hima.mori.maintext:text('不容于社会的杀人犯、小偷、中年色狼等等全都要进到这间刑务所来，感觉就像是罪犯的主题乐园吧 ')
   
   Scene.bg.hima.mori.maintext:text('而轻一点的罪行……像超速行驶似乎只要付钱给国家就行了 ')
   
   Scene.bg.hima.mori.maintext:text('绞首啦、刑务所啦、钱啦…… ')
   
   Scene.bg.hima.mori.maintext:text('我们的国家根据不同的罪行规定了各式各样细微的责罚，不过日本大致上不过日本大致上就分成这三种 ')
   
   Scene.bg.hima.mori.maintext:text('像日本那样的处罚，身处这个国家的我们不由得会想：这样真的可以让人改过向善吗？ ')
   
   Scene.bg.hima.mori.maintext:text('啊、只是呢，要是我们被人反问：仅仅禁止杀人犯拥有小孩，这世界就会和平吗？恐怕也是难说难说啊 ')
   
   Scene.bg.hima.mori.maintext:text('我国的精英分子总是在谈论着利己性的遗传基因如何、犯罪哲学如何、宗教方面的自他对立又是如何之类的事情，而我们总是有意无意地服从着他们所订立的法律 ')
   
   Scene.bg.hima.mori.maintext:text('说到无意中……生于『日本』的人们应该也是在无意中的服从上层规定的吧 ')
   
   Scene.bg.hima.mori.maintext:text('所以啦，对于已经决定的法律或是制度，我也不太会去评论 ')
   
   Scene.bg.hima.mori.maintext:text('重点是不管是在『日本』、还是在这个『国家』，到底要怎么在那样的世界中生活下去 ')
   
   Scene.bg.hima.mori.maintext:text('还有像我这样的小角色要怎么跟大姐姐共谱恋曲，这才是需要探讨的地方 ')
   
   Scene.bg.hima.mori.maintext:text('――不久的未来 ')
   
   Scene.bg.hima.mori.maintext:text('――以及一个离得不算远的地方 ')

   -- Scene:save_scene()
   
   Scene.bg.hima.mori:remove('maintext')
   
   Scene.bg.hima:remove('mori')
   
   Scene.bg:remove('hima')
   
   Scene:remove('bg')

   Scene:insert('bg',
	    {
	       data = {
		  attribute = 'sprite',
		  clip = ClipFunc.stable(0, 0, 800, 600),  
		  location = LocationFunc.stable(0, 0),
		  img = 'data/rogo.bmp',
	       }
	    }
	 )


   -- Scene:fade_out()
   
   TimerFunc:ScriptEvent(2000)

   Scene:remove('bg')

   Scene:insert('bg',
		{
		   data = {
		      attribute = 'sprite',
		      clip = ClipFunc.stable(0, 0, 800, 600), 
		      location = LocationFunc.stable(0, 0),
		      img = 'data/bg_01a.png',
		   }
		}
	     )

   Scene.bg:insert('maintext',
   		   {
   		      data = { 
   			 attribute = 'textbox',
   			 clip = ClipFunc.stable(0, 0, 800, 200) ,
   			 location = LocationFunc.stable(0, 400),
   			 frame_event = TimerFunc.FrameTimer(100),
			 
   			 OnMouseRange = RangeCheckFunc.retangle(0, 0, 800, 600),
			 
   			 wordlayer = {
   			    font_name = 'data/simhei.ttf',
   			    font_size = 20,
   			    box = 'data/w_win.bmp',
   			    x = 30,
   			    y = 70,
   			    width = 720,
   			    height = 200,
   			    text_color = 0xff000000
   			 }
   		      }
		      
   		   }
   		)

   Scene.bg.maintext:text('毫不回首的六小时步行。')

   Scene.bg.maintext:text('乡下地方至少是会有公车运行的。')

   Scene.bg.maintext:text('穷乡僻壤也许会有个感觉和善的老爷爷开着货运车让你坐个顺风车。')
   
   Scene.bg.maintext:text('不过，我的故乡与其说是乡下，不如说是秘境更合适。')

   Scene.bg.maintext:text('一整片的黄色，是来自于根本搞不清楚怎么繁茂起来的向日葵花群。')

   Scene.bg.maintext:text('山上的风就像是在汲取着盛夏的热气，其爽快感跟就在不久前还黏附在肌肤上的都市大厦风是截然不同的。')

   Scene.bg.maintext:text('我仰头望向高挂天际发出炽热光芒的太阳。')

   Suspend()
end

local function bullet_server()
   local bulletServer = Scene.bulletServer
   local print = print
   local table = table
   local socket = require('socket')
   local server = socket.bind('*', 0)
   local client = {}
   local ip, port = server:getsockname()
   print('The ip and port of bullet_server is ', ip, port)

   bulletServer.setBulletTextSpeed(1)
   bulletServer.setBulletTextFont('data/simhei.ttf', 30)

   server:settimeout(0.01)
   while 1 do
      local remote, err = server:accept()
      if remote then
	 remote:settimeout(0.01)
	 table.insert(client, remote)
      end
      local active = socket.select(client, nil, 0.01)
      if active then
	 for i = 1, #active do
	    local msg = active[i]:receive()
	    bulletServer.createBulletText(msg, 0xffffffff)
	 end
      end
      WaitFrame(1)
   end
end

Script = subRoutine(test_chapter)
Server = subRoutine(bullet_server)
