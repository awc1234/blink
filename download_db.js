var express = require('express');
var fs = require('fs');
var app = express();

mysql = require('mysql');
var connection = mysql.createConnection({
	host: 'localhost',
	user: 'me',
	password: 'mypassword',
	database: 'mydb'
})
connection.connect();

function insert_sensor(device, unit, type, value, seq, ip)
{
	obj = {}; obj.seq = seq; obj.device = device; 
	obj.unit = unit; obj.type = type; obj.value = value;
	obj.ip = ip.replace(/^.*:/, '')

	var query = connection.query('insert into sensors set?',obj,
		function(err,rows,cols){
		if(err)throw err;
		console.log("database insertion ok=%j",obj);
		});
}

app.get('/',function(req,res){
	res.end('welcome 20131572 server.');
});

app.get('/log',function(req,res){
	r = req.query;
	console.log("GET %j",r);
	insert_sensor(r.device, r.unit, r.type, r.value, r.seq, req.connection.remoteAddress);
	res.end("Got "+JSON.stringify(req.query));
});


app.get("/download",function(req,res){
	console.log("param="+req.query);
	var qstr = 'select * from sensors ';
	var filepath = __dirname + '/data.csv';
	console.log("filepath: "+filepath);
	connection.query(qstr, function(err, rows, cols){
		if(err){
			throw err;
			res.send('query error: '+qstr);
			return;
		}
		console.log("Got"+rows.length+" records");
		html = ""
		ans  = ""
		for(var i=0; i< rows.length;i++){
			ans+= rows[i].id+","+ rows[i].seq+","+ rows[i].device+","
				+ rows[i].unit+","+ rows[i].type+","+ rows[i].value+","
				+ rows[i].ip+","+rows[i].time+"\n";
			html+=String(JSON.stringify(rows[i]));
			html+=String("\n");
		}
		fs.writeFile('data.csv',ans,'utf8',function(err){
			console.log("FileWrite success.");
		});
		fs.readFile('data.csv','utf8',function(err, data){
			console.log("FILERead success.");
			res.download(filepath);	
		});
//		res.send(html);
	})
});



var server = app.listen(8083,function() {
	var host = server.address().address
	var port = server.address().port
	console.log('listening at http://%s.%s',host,port)
});



