# Json Robot
![test](https://travis-ci.com/tvytlx/jsonbot.svg?token=kHMnD6ux3VYAzZeWzvQz&branch=master)

我们知道人工智能标记语言 `AIML` 是基于 `xml` 文件实现的，但由于 `AIML` 不原生支持中文，而且模板编写过于繁琐，所以作者想以面向中文环境，以及书写模板简单的出发点来重新实现 `AIML` 的简易版，并且将模板文件改为 `Json` 格式，存储基于本地文件系统。 [Online Demo](http://arctanx.space/chat.html)
    
## 模板示例

```json
[
    {
        "ask":  ["你好S","你好", "U你好S", "U你好"],
        "reply": ["你好。", "很高兴见到你。"]
    },
    {
        "ask": ["今天天气S", "今天S天气S", "U今天S天气S","今天天气", "今天S天气"],
        "reply": ["T{天气}"]
    },
    {
        "ask": ["你叫S", "你名字S", "你S名字S", "U你S名字", "你是谁"],
        "reply": ["我叫Matrix(v0.1)，一个简单的可配置通用机器人，这里有我的说明哦 http://github.com/tvytlx/jsonbot"]
    },
    {
        "ask": ["你是S做的S", "你是S做的", "你的作者", "你的作者S"],
        "reply": ["作者：Xiao Tan <tvytlx@gmail.com>"]
    }
]
```

## 生成的存储文件

```shell
...
\你好
    template.json
    \%S
        template.json
\%U
    \你好
    template.json
        \%S
        tempalte.json
...
( template.json 内容为: ["你好。", "很高兴见到你。"])
```

## 生成的全局唯一索引文件

```json
{
    "template": "root",
    "nodes_count": 0,
    "word": "",
    "child_nodes": [
        {
            "word": "你好",
            "child_nodes": [
                {
                    "word": "%S",
                    "child_nodes": [],
                    "isLeaf": true
                }
            ],
            "isLeaf": true
        }
        ...
```

## 目前已经实现的功能
- `AILM` [最基本的匹配规则](http://www.alicebot.org/documentation/matching.html)。类似于正则，可以实现模糊查找。
- 模板内容重定向搜索。
- 多个问题对应一个模板文件。模板里的回答随机。
- 模板里嵌套指定模板。
	+ 天气: 今天无锡的天气是：`{天气}`
	+ 百度: 来自百度百科的内容：`{百度}`