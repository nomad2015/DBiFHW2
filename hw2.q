/ $Id$
/ author:  Xiaobo He
/ descrip: Calculate vwap from loaded cvs data file 


/ prints a logline
/ msg_: type string
.taq.logline: {[msg_]
  0N!(string .z.Z), "   taq |  ", msg_;
  };


/ import a trade data csv file into kdb. 
/ file_: type string.
.taq.import_file: {[file_]

  / load the trade file into a 'trade' table
  `trade_data set
    ("DTSFI"; enlist ",") 0: hsym "S"$ file_;

  .taq.logline["file loaded: ", file_];
  .taq.logline["  records:  ", (string count trade_data)];

  };


/ calculate vwap
.taq.cal_vwap_file: {[filedata_;fileresult_]
  /import data file
  .taq.import_file[filedata_];

  /calculate vwap by date and symbol
  result :select vwap:(sum Price*Volume)%(sum Volume) by Date,Symbol from trade_data;
  
  /output result into csv file
  (hsym "S"$ fileresult_) 0: .h.cd result;
  };
