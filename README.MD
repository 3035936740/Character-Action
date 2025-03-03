# Character☆Action
<!--gold sponsors start-->
<p align="center">
<img width="256px" src="https://github.com/3035936740/Character-Action/blob/main/favicon.png">
</p>
<!--gold sponsors end-->
这个项目是用来控制角色的,可以做什么呢试试就知道啦(
启动这个程序后下面是个curl的例子
<pre><code>curl -X POST 127.0.0.1:8080/send \
-H "Content-Type: application/json" \
-d '{"message": "我现在很生气!", "mood": "angry"}'</code></pre>
注意: 请确保将系统默认编码方法为UTF8,不然就乱码喽~

## C++标准是多少?
C++23

## C++用了哪些库?
<pre><code>- SFML
- nlohmann json
- yaml-cpp
- cpp httplib</code></pre>
