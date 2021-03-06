
var palette = new Rickshaw.Color.Palette({scheme: 'munin'});


var graphs = [];
function graphsRender() {
	graphs.forEach(function(graph) {
		graph.render();
	});
}

function addGraph(databankNames, elementName) {
	var end = new Date().addSeconds(90);
	var timeInterval = 500;
	var timeDuration = 1.8 * 60 * 1000;
	// instantiate our graph!
	var things = [];
	databankNames.forEach(function(databaseName) {
		things.push({ name: databaseName, color: palette.color() });
	});
	$("#" + elementName).append("<div id=\"l_"+elementName+"\"></div><div id=\"g_"+elementName+"\"></div>");
	var graph = new Rickshaw.Graph({
		element: document.getElementById("g_"+elementName),
		renderer: 'line',
		interpolation: "linear",
		series: new Rickshaw.Series.FixedDuration(things, undefined, {
			timeInterval: timeInterval,
			maxDataPoints: timeDuration / timeInterval,
		})
	});
	graph.configure({
		width: $("#" + elementName).width(),
		height: $("#" + elementName).height()
	});
	graphs.push(graph);
	graph.render();
	var ticksTreatment = 'glow';
	var xAxis = new Rickshaw.Graph.Axis.Time( {
		graph: graph,
		ticksTreatment: ticksTreatment,
		timeFixture: new Rickshaw.Fixtures.Time.Local()
	} );
	xAxis.render();
	var yAxis = new Rickshaw.Graph.Axis.Y({
		graph: graph,
		ticksTreatment: ticksTreatment,
		tickFormat: Rickshaw.Fixtures.Number.formatKMBT
	});
	yAxis.render();
	var hoverDetail = new Rickshaw.Graph.HoverDetail({
		graph: graph,
		xFormatter: function(x) { return new Date(x * 1000).toString('HH:mm:ss'); },
		yFormatter: function(y) { return Math.floor(y * 10)/10 }
	});
	var legend = new Rickshaw.Graph.Legend( {
		graph: graph,
		element: document.getElementById("l_"+elementName)
	} );
	var shelving = new Rickshaw.Graph.Behavior.Series.Toggle( {
		graph: graph,
		legend: legend
	} );
	/*var order = new Rickshaw.Graph.Behavior.Series.Order( {
		graph: graph,
		legend: legend
	} );*/
	var highlighter = new Rickshaw.Graph.Behavior.Series.Highlight( {
		graph: graph,
		legend: legend
	} );
	// add some data every so often
	var i = 0;
	setInterval(function() {
		var data = {};
		databankNames.forEach(function(databaseName) {
			var value = getDataValue(databaseName);
			data[databaseName] = value;
		});
		graph.series.addData(data);
	}, timeInterval);
	return graph;
}
