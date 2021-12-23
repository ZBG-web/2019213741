;window.onload=function(){
    //获取标签元素方法
    function $(idName){
        return document.getElementById(idName);
    }
    //获取样式使用最终值的函数
    function getStyle(ele,atter){
        var res=null;
        if(ele.currentStyle){
            res=ele.currentStyle[atter];
        }else{
            res=window.getComputedStyle(ele,null)[atter];
        }
        return parseFloat(res);
    }
    //获取需要使用到的标签元素
    var game=$("game")
    ,   gameStart=$("gameStart")
    ,   gameEnter=$("gameEnter")
    ,   myPlane=$("myPlane")
    ,   bulletsP=$("bullets")
    ,   enemysP=$("enemys")
    ,   s=$("scores").firstElementChild.firstElementChild;
    //获取需要使用到的元素样式
    //1.获取游戏界面的宽高
    var gameW=getStyle(game,"width")
    ,   gameH=getStyle(game,"height");
    //2.游戏界面的左上外边距
    var gameML=getStyle(game,"marginLeft")
    ,   gameMT=getStyle(game,"marginTop");
    //3.获取己方飞机的宽高
    var myPlaneW=getStyle(myPlane,"width")
    ,   myPlaneH=getStyle(myPlane,"height");
    //4.获取子弹的宽高
    var bulletW=5
    ,   bulletH=11;
    //声明全局变量
    var gameStatus=false
    ,   a=null//创建子弹的定时器
    ,   b=null//创建敌机的定时器
    ,   c=null//背景图运动的定时器
    ,   backgroundPY=0//背景图y轴的值
    ,   bullets=[]//子弹元素的集合
    ,   enemys=[]//敌机元素的集合
    ,   scores=0
    ;
    //开始游戏
    gameStart.firstElementChild.onclick=function(){
        gameStart.style.display="none";
        gameEnter.style.display="block";
        //给当前的文档添加键盘事件
        document.onkeyup=function(evt){
            var e=evt||window.event;
            var keyVal=e.keyCode;
            if(keyVal==32){
                if(!gameStatus){
                    scores=0;
                    this.onmousemove=myPlaneMove;
                    bgMove();//实现背景图的运动
                    shot();//产生子弹
                    appearEnemy();//出现敌机
                    if(bullets.length!=0)reStart(bullets,1);
                    if(enemys.length!=0)reStart(enemys);
                }else{
                    this.onmousemove=null;
                    clearInterval(a);
                    clearInterval(b);
                    clearInterval(c);
                    a=null;
                    b=null;
                    c=null;
                    clear(bullets);
                    clear(enemys);
                }
                gameStatus=!gameStatus;
            }
        }
    }
    //己方飞机的移动
    function myPlaneMove(evt){
        var e=evt||window.event;
        var mouse_x=e.x||e.pageX
        ,   mouse_y=e.y||e.pageY;
        //计算得到鼠标移动时己方飞机的左上边距
        var last_myPlane_left=mouse_x-gameML-myPlaneW/2
        ,   last_myPlane_top=mouse_y-gameMT-myPlaneH/2;
        //控制飞机不能脱离游戏界面
        if(last_myPlane_left<=0){
            last_myPlane_left=0;
        }else if(last_myPlane_left>=gameW-myPlaneW){
            last_myPlane_left=gameW-myPlaneW;
        }
        if(last_myPlane_top<=0){
            last_myPlane_top=0;
        }else if(last_myPlane_top>=gameH-myPlaneH){
            last_myPlane_top=gameH-myPlaneH;
        }
        myPlane.style.left=last_myPlane_left+"px";
        myPlane.style.top=last_myPlane_top+"px";

    }
    //单位时间内创建子弹
    function shot(){
        if(a) return ;
        a=setInterval(function(){
            createBullet();
           /*console.log(bullets);*/
        },100);
    }
    //创建子弹
    function createBullet(){
        var bullet=new Image();
        bullet.src="images/bullet1.png";
        bullet.className="b";
        //确定子弹的位置
        var myPlaneL=getStyle(myPlane,"left")
        ,   myPlaneT=getStyle(myPlane,"top");
        var bulletL=myPlaneL+myPlaneW/2-bulletW/2
        ,   bulletT=myPlaneT-bulletH;
        bullet.style.left=bulletL+"px";
        bullet.style.top=bulletT+"px";
        bulletsP.appendChild(bullet);
        bullets.push(bullet);
        move(bullet,"top");
    }
    //子弹的运动
    function move(ele,atter){
        var speed=-8;
        ele.timer=setInterval(function(){
            var moveVal=getStyle(ele,atter);
            //消除子弹
            if(moveVal<=-bulletH){
                clearInterval(ele.timer);
                ele.parentNode.removeChild(ele);
                bullets.splice(0,1);
            }else{
                ele.style[atter]=moveVal+speed+"px";
            }

        },10);
    }
    //创建敌机对象
    var enemysObj={
        enemy1:{
            width:57,
            height:43,
            score:100,
            hp:100
        },
        enemy2:{
            width:69,
            height:99,
            score:500,
            hp:500
        },
        enemy3:{
            width:169,
            height:258,
            score:1000,
            hp:1000
        }
    }
    //创建敌机的定时器
    function appearEnemy(){
        if(b) return ;
        b=setInterval(function(){
            createEnemy();
            /*console.log(enemys);*/
            delEnemy();
           /* console.log(enemys);*/
        },1000);
    }
    //制造敌机的函数
    function createEnemy(){
        //敌机出现概率的数据
        var percentDate=[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,3];
        //敌机的类型
        var enemyType=percentDate[Math.floor(Math.random()*percentDate.length)];
        //得到当前随机敌机的数据
        var enemyData=enemysObj["enemy"+enemyType];
        //创建敌机所在的元素
        var enemy=new Image(enemyData.width,enemyData.height);
        enemy.src="images/enemy"+enemyType+".png";
        enemy.score=enemyData.score;
        enemy.t=enemyType;
        enemy.hp=enemyData.hp;
        enemy.className="e";
        enemy.dead=false;
        //确定当前敌机出现的位置
        var enemyL=Math.floor(Math.random()*(gameW-enemyData.width+1))
        ,   enemyT=-enemyData.height;
        enemy.style.left=enemyL+"px";
        enemy.style.top=enemyT+"px";
        enemysP.appendChild(enemy);
        enemys.push(enemy);
        enemyMove(enemy,"top");
    }
    //敌机的运动
    function enemyMove(ele,attr){
        var speed=null;
        if(ele.t==1){
            speed=1.5;
        }else if(ele.t==2){
            speed=1;
        }else if(ele.t==3){
            speed=0.5;
        }
        ele.timer=setInterval(function(){
            var moveval=getStyle(ele,attr);
            if(moveval>=gameH){
                clearInterval(ele.timer);
                enemysP.removeChild(ele);
                enemys.splice(0,1);
            }else{
                ele.style[attr]=moveval+speed+"px";
                danger(ele);
                gameOver();
            }
        },10);
    }
    //消除子弹和敌机运动的定时器
    function clear(childs){
        for(var i=0;i<childs.length;i++){
            clearInterval(childs[i].timer);
        }
    }
    //暂停游戏后开始游戏
    function reStart(childs,type){
        for(var i=0;i<childs.length;i++){
            type==1?move(childs[i],"top"):enemyMove(childs[i],"top");
        }
    }
    //开始游戏之后的背景图的运动
    function bgMove(){
        c=setInterval(function(){
            backgroundPY+=0.5;
            if(backgroundPY>=gameH){
                backgroundPY=0;
            }
            gameEnter.style.backgroundPositionY=backgroundPY+"px";
        },10);
    }
    //检测子弹和敌机的碰撞
    function danger(enemy){
        for( var i=0;i<bullets.length;i++){
            //得到子弹的左上边距
            var bulletL=getStyle(bullets[i],"left")
            ,   bulletT=getStyle(bullets[i],"top");
            //得到敌机的左上边距
            var enemyL=getStyle(enemy,"left")
            ,   enemyT=getStyle(enemy,"top");
            //得到敌机的宽高
            var enemyW=getStyle(enemy,"width")
            ,   enemyH=getStyle(enemy,"height");
            var condition=bulletL+bulletW>=enemyL&&bulletL<=enemyL+enemyW&&bulletT<=enemyT+enemyH&&bulletT+bulletH>=enemyT;
            if(condition){
                clearInterval(bullets[i].timer);
                bulletsP.removeChild(bullets[i]);
                bullets.splice(i,1);
                enemy.hp -=100;
                if(enemy.hp==0){
                    clearInterval(enemy.timer);
                    enemy.src="images/bz"+enemy.t+".png";
                    enemy.dead=true;
                    scores+=enemy.score;
                    s.innerHTML=scores;
                }
            }
        }
    }
    function delEnemy(){
        for(var i=enemys.length-1;i>=0;i--){
            if(enemys[i].dead){
                (function(index){
                    enemysP.removeChild(enemys[index]);
                    enemys.splice(index,1);
                })(i)
            }
        }
    }
    //飞机碰撞，结束游戏
    function gameOver(){
        for(var i=0;i<enemys.length;i++){
            if(!enemys[i].dead){
                var enemyL=getStyle(enemys[i],"left")
                ,   enemyT=getStyle(enemys[i],"top");
                var enemyW=getStyle(enemys[i],"width")
                ,   enemyH=getStyle(enemys[i],"height");
                var myPlaneL=getStyle(myPlane,"left")
                ,   myPlaneT=getStyle(myPlane,"top");
                var condition=myPlaneL+myPlaneW>=enemyL&&myPlaneL<=enemyL+enemyW&&myPlaneT<=enemyT+enemyH&&myPlaneT+myPlaneH>=enemyT;
                if(condition){
                    clearInterval(a);
                    clearInterval(b);
                    clearInterval(c);
                    a=null;
                    b=null;
                    c=null;
                    remove(bullets);
                    remove(enemys);
                    bullets=[];
                    enemys=[];
                    document.onmousemove=null;
                    alert("Game over:"+scores+"分");
                    gameStart.style.display="block";
                    gameEnter.style.display="none";
                    myPlane.style.left="189px";
                    myPlane.style.top=gameH-myPlaneH+"px";               
                }
            }
        }
    }
    scores=0;
    //删除元素
    function remove(childs){
        for(var i=childs.length-1;i>=0;i--){
            clearInterval(childs[i].timer);
            childs[i].parentNode.removeChild(childs[i]);
        }

    }
}
