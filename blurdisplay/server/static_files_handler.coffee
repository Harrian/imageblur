fs = Npm.require('fs')
mime = Npm.require('mime')
WebApp.rawConnectHandlers.use (req, res, next) ->
  re = /^\/static\/(.*)$/.exec(req.url)
  if re isnt null # Only handle URLs that start with /static/*
    filePath = process.env.PWD + "/public/.#static/" + re[1]
    type = mime.lookup(filePath)
    data = fs.readFileSync(filePath, data)
    res.writeHead 200,
      "Content-Type": type

    res.write data
    res.end()
  else # Other urls will have default behaviors
    next()
  return