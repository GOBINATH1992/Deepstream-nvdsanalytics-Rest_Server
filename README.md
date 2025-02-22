# Deepstream-nvdsanalytics-Rest_Server
Deepstream nvdsanalytics plugin with Rest Server support 



This sample demonstrates nvdsanalytics  plguin control using Rest api server.
Run install.sh  to install custom plugin with rest support


curl -XPOST 'http://localhost:9001/analytics/update' -d '{
    "stream": {
        "stream_id": 1,
        "roi_count": 2,
        "roi": [{
                "pts": "5,50,1800,50,1800,1000,50,1000",
				"label": "RF",
				"class_id": "-1",
				"enable" : 1,
				"inverse_roi": 0,
				"stream_id" : 1
				},
				{
                "pts": "100,100,1800,100,1800,1000,100,1000",
				"label": "RF1",
				"class_id": "-1",
				"enable" : 1,
				"inverse_roi": 0,
				"stream_id" : 1
				}
        ],
		"line_count": 1,
        "line": [{
                "pts": "789,672,1084,900,851,773,1203,732",
				"label": "RFL",
				"class_id": "0",
				"enable" : 1,
				"extended": 0,
				"mode": "loose",
				"stream_id" : 1
				}
        ]
    }
  }' 

