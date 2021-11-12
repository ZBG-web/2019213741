function getTop(e)
{
    var offset = e.offsetTop;
    if(e.offsetParent != null) 
    {
        offset += getTop(e.offsetParent);
    }
    return offset;
}

function getLeft(e)
{
    var offset = e.offsetLeft;
    if (e.offsetParent != null)
    {
        offset += getLeft(e.offsetParent);
    }
    return offset;
}

function mOver(obj)
{
    let b = document.getElementById("message");
    let time = document.getElementById("time");
    let atime = document.getElementById("atime");
    let address = document.getElementById("address");
    let teacher = document.getElementById("teacher");
    if (b.offsetParent != null)
    {
        var top = getTop(obj) + obj.offsetHeight - b.offsetParent.offsetTop ;
        var left = getLeft(obj) + obj.offsetWidth - b.offsetParent.offsetLeft;
    }
    else
    {
        var top = getTop(obj) + obj.offsetHeight ;
        var left = getLeft(obj) + obj.offsetWidth;
    }
    console.log(typeof(b.style.top));
    console.log(b.style.top);
    if (obj.innerHTML == "编译原理")
    {
        time.value = "1-20周";
        atime.innerHTML = "周二1-2节；周四7-8节";
        address.innerHTML = "n211";
        teacher.innerHTML = "蔡霞";
        b.style.top = top.toString() + "px";
        b.style.left = left.toString() + "px";
        b.style.display = "block";
    }
    else if (obj.innerHTML == "信息检索技术")
    {
        time.innerHTML = "1-18周";
        atime.innerHTML = "周二7-8节；周四1-2节";
        address.innerHTML = "n108";
        teacher.innerHTML = "张茂元";
        b.style.top = top.toString() + "px";
        b.style.left = left.toString() + "px";
        b.style.display = "block";
    }
    else if (obj.innerHTML == "操作系统原理")
    {
        time.innerHTML = "1-19周";
        atime.innerHTML = "周三3-4节；周五1-2节";
        address.innerHTML = "n211";
        teacher.innerHTML = "李源";
        b.style.top = top.toString() + "px";
        b.style.left = left.toString() + "px";
        b.style.display = "block";
    }
    else if (obj.innerHTML == "微机原理与接口技术")
    {
        time.innerHTML = "1-19周";
        atime.innerHTML = "周一3-4节；周三7-8节";
        address.innerHTML = "n113";
        teacher.innerHTML = "金汉均";
        b.style.top = top.toString() + "px";
        b.style.left = left.toString() + "px";
        b.style.display = "block";
    }
    else if (obj.innerHTML == "习近平新时代中国特色社会主义思想概论")
    {
        time.innerHTML = "1-19周";
        atime.innerHTML = "周四3-4节";
        address.innerHTML = "n215";
        teacher.innerHTML = "张艳斌";
        b.style.top = top.toString() + "px";
        b.style.left = left.toString() + "px";
        b.style.display = "block";
    }
    else if (obj.innerHTML == "Web程序设计")
    {
        time.innerHTML = "1-19周";
        atime.innerHTML = "周四5-6节";
        address.innerHTML = "n108";
        teacher.innerHTML = "涂新辉";
        b.style.top = top.toString() + "px";
        b.style.left = left.toString() + "px";
        b.style.display = "block";
    }
    else if (obj.innerHTML == "民俗丛谈")
    {
        time.innerHTML = "1-19周";
        atime.innerHTML = "周一7-8节";
        address.innerHTML = "9403";
        teacher.innerHTML = "张静";
        b.style.top = top.toString() + "px";
        b.style.left = left.toString() + "px";
        b.style.display = "block";
    }
    else if (obj.innerHTML == "文学经典赏读")
    {
        time.innerHTML = "1-16周";
        atime.innerHTML = "周三9-10节";
        address.innerHTML = "8104";
        teacher.innerHTML = "付林鹏";
        b.style.top = top.toString() + "px";
        b.style.left = left.toString() + "px";
        b.style.display = "block";
    }
}

function mOut()
{
    let b = document.getElementById("message");
    b.style.display = "none";
}