local Scene = SceneManager.create() --每个scene均设metatable的__index，所有的类函数放__index
Scene.Setting.setFont('data/simhei.ttf', 20)

local function test_chapter()

   Scene:insert('bg',
		{
		   data = {
		      attribute = 'sprite',
		      location = LocationFunc.stable(0, 0), 
		      clip = ClipFunc.move(1000, 0, 800, 600, -0.5, 0, 0, 0),
		      img = 'data/yama.bmp',
		      frame_event = TimerFunc.FrameTimer(200)
		   }
		}
	     )
   
   Scene.bg:insert('hima', --data中每项以table, function 或 string 的形式出现
                {
		   data = {
		      attribute = 'sprite',
		      clip = ClipFunc.move(1000, 0, 800, 600, -1, 0, 0, 0),
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

   local maintext = Scene.bg.hima.mori.maintext

   maintext:text('先来个自我介绍吧')

   maintext:text('我是森田贤一 ')

   maintext:text('最喜欢的就是科幻小说跟大姐姐 ')
   
   maintext:text('我常看的一本书中有一个名为『日本』的国家 ')
   
   maintext:text('你或许也已经知道了，这是一个会让人产生浓厚兴趣的奇妙岛国 ')
   
   maintext:text('你问什么地方有意思？ ')
   
   maintext:text('比如说在现实里，要是杀了人不是就要背负『一生不得拥有小孩的义务』吗？ ')
   
   maintext:text('之后就会受到一群叫『特别高等人』的恐怖家伙的保护观察 ')
   
   maintext:text('不过『日本』并不同 ')
   
   maintext:text('杀人是要被以绞刑处死的 ')
   
   maintext:text('又或是会被关进一个叫刑务所的地方十几二十年的，可能是一辈子也不一定 ')
   
   maintext:text('刑务所好像又称牢房或是监狱，我们的国家里并不存在这种设施，所以挺有意思的 ')
   
   maintext:text('不容于社会的杀人犯、小偷、中年色狼等等全都要进到这间刑务所来，感觉就像是罪犯的主题乐园吧 ')
   
   maintext:text('而轻一点的罪行……像超速行驶似乎只要付钱给国家就行了 ')
   
   maintext:text('绞首啦、刑务所啦、钱啦…… ')
   
   maintext:text('我们的国家根据不同的罪行规定了各式各样细微的责罚，不过日本大致上不过日本大致上就分成这三种 ')
   
   maintext:text('像日本那样的处罚，身处这个国家的我们不由得会想：这样真的可以让人改过向善吗？ ')
   
   maintext:text('啊、只是呢，要是我们被人反问：仅仅禁止杀人犯拥有小孩，这世界就会和平吗？恐怕也是难说难说啊 ')
   
   maintext:text('我国的精英分子总是在谈论着利己性的遗传基因如何、犯罪哲学如何、宗教方面的自他对立又是如何之类的事情，而我们总是有意无意地服从着他们所订立的法律 ')
   
   maintext:text('说到无意中……生于『日本』的人们应该也是在无意中的服从上层规定的吧 ')
   
   maintext:text('所以啦，对于已经决定的法律或是制度，我也不太会去评论 ')
   
   maintext:text('重点是不管是在『日本』、还是在这个『国家』，到底要怎么在那样的世界中生活下去 ')
   
   maintext:text('还有像我这样的小角色要怎么跟大姐姐共谱恋曲，这才是需要探讨的地方 ')
   
   maintext:text('――不久的未来 ')
   
   maintext:text('――以及一个离得不算远的地方 ')

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

   local bg = Scene.bg
   TimerFunc:ScriptEvent(2000)

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

   maintext = Scene.bg.maintext
   
   maintext:setVisible(TextFunc.SET, 2)

   bg.data.img = 'data/bg_01a.png'
   bg:update()

   maintext:setVisible(TextFunc.UNSET, 2)

   maintext:text('毫不回首的六小时步行。')

   maintext:text('乡下地方至少是会有公车运行的。')

   maintext:text('穷乡僻壤也许会有个感觉和善的老爷爷开着货运车让你坐个顺风车。')
   
   maintext:text('不过，我的故乡与其说是乡下，不如说是秘境更合适。')

   maintext:text('一整片的黄色，是来自于根本搞不清楚怎么繁茂起来的向日葵花群。')

   maintext:text('山上的风就像是在汲取着盛夏的热气，其爽快感跟就在不久前还黏附在肌肤上的都市大厦风是截然不同的。')

   maintext:text('我仰头望向高挂天际发出炽热光芒的太阳。')

   maintext:setVisible(TextFunc.SET, 2)

   bg.data.img = 'data/bg_24a.png'
   bg.data.frame_event = TimerFunc.FrameTimer(100)
   bg.data.clip = ClipFunc.move(0, 621, 800, 600, 0, -32,  0, 1)
   bg:update()
   TimerFunc:ScriptEvent(2000)
   bg.data.frame_event = nil

   maintext:setVisible(TextFunc.UNSET, 2)

   maintext:text('我到啦啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊。')
   
   bg.data.img = 'data/bg_01a.png'
   bg.data.clip = ClipFunc.stable(0, 0, 800, 600)
   bg:update()

   maintext:text('呼呜呜～～～')

   maintext:text('深呼吸。')

   maintext:text('我在砂土路上盘腿坐下。')

   maintext:setVisible(TextFunc.SET, 2)

   bg.data.clip = ClipFunc.move(0, 0, 800, 600, 0, 30, 0, -2)
   bg.data.frame_event = TimerFunc.FrameTimer(100)
   TimerFunc:ScriptEvent(2000)
   bg.data.frame_event = nil

   maintext:setVisible(TextFunc.UNSET, 2)

   maintext:text('你应该也知道，人啊、要是一个人独处得太久是会发疯的。')

   maintext:text('好比我，七岁的时候就被附近的危险大哥哥监禁过')

   maintext:text('十岁被带到北方国家，十三岁进入新兴宗教')

   maintext:text('十五岁的时候啊，进到ＳＭ小屋被彻底调教成了一个重度Ｍ')

   maintext:text('理所当然的流程，没有双亲')

   maintext:text('母亲生下我后就马上去另一个世界报到了。留给我的最后几句话是『红萝卜要吃光光哦』『小鸟都是吃牛骨粉才长得好的，注意、注意』这些个实在是十分健康的建议')

   maintext:text('托她的福，我的身体像钢铁一样强韧')

   maintext:text('老爸也不差，晚上是职业摔角手，白天则是司法代书人的这么一个高学识格斗家')

   maintext:text('然而，号称最强面具人的老爸他，为了保护一名冲出车道的幼女而化为了天上一颗星。享年３８岁')

   maintext:text('于是，克服了无数逆境、困难、心理创伤、洗脑、调教、至亲的死，才成就了现在的我')

   maintext:text('在我这样的年纪当中，我已经是最强、最完整，毫无成长余地可言的完美超人')

   maintext:text('要是没有这种程度，是没办法接受『特别高等人』考试的吧')

   maintext:text('大致上说完后感觉清爽畅快的我，打开了一路上带过来的学生书包。')

   maintext:text('完美超人的我，从学生书包开始就非比寻常」')

   maintext:text('银色的铝合金公事箱。')

   maintext:text('我从当中取出一管仍是非比寻常的超高级象牙烟斗，以优雅的动作含在口中。')

   maintext:text('管它什么学生身份之类的，就算抽烟，只要不被人抓到就行」')

   maintext:text('啊、实际上不是烟而是药啦」')

   maintext:text('吸～～～……呼～～～……」')

   maintext:text('吸～～～……呼～～～……」')

   maintext:text('啊啊、堕落了啊。')

   maintext:text('堕落的感觉真好。')

   maintext:text('呼……咈咈咈……唔嘿嘿嘿嘿嘿」')

   maintext:text('啊～，舒服舒服」')

   maintext:text('好想死一回啊……。')

   maintext:text('意识慢慢模糊起来。')

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
