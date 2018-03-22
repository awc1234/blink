const express = require('express')
const app = express()
const fs = require('fs')

var seq = 0
app.get('/update', function(req, res){
       fs.appendFile('log.txt',JSON.stringify(req.query)+"\n", function(err){
           if(err) throw err
           //console.log("Got "+String(seq++)+" "+JSON.stringify(req.query))
           res.end("Got "+String(seq++)+" "+JSON.stringify(req.query))
       });
})
app.get('/get', function (req, res) {
    var count = parseInt(JSON.parse(JSON.stringify(req.query)).count);
    fs.readFile('log.txt','utf8',(err,data)=>{
        if (err) throw err;
        var ans = "";
        var array = data.split("\n"), length=array.length;
        count = length-1 < count ? length-1 : count;
        //console.log("count: "+count);
        for(var i=length-count-1;i<length-1;i++)//for(var i=0; i<count; i++)
        {
            //console.log(array[i]+"\n");
            var value = JSON.parse(array[i]);
            ans+=value.api_key+","+String(parseFloat(value.field1).toFixed(2))+"\n";
            /*for (var key in value) {ans += value[key];if(key=='api_key')ans+=',';else ans+='\n';}*/
        }
        //console.log(ans);
        res.end(ans);   // res.end(data);
    });
});
app.listen(8080, ()=>console.log('listening on port 8080!'))

