skywarp_cpp

Data streaming and rpc enabler library for c++ applications

###Introduction


Skywarp++ is an [(BSD license)](http://es.wikipedia.org/wiki/Licencia_BSD) open source server library that enables the use of remote procedure for exposition of functionalities and real time data [streaming](http://en.wikipedia.org/wiki/Stream_(computing)) capabilities to any application written in c++.

The c++ applications that uses skywarp++, can expose your functionalities through of [JSON-RPC 2.0](http://www.jsonrpc.org/specification) subprotocol in order to be used by clients that supports websocket transport protocol.

Furthermore, skywarp++, enable  application to implement real time data streaming to your client in a push model, through of a built-in publish-subscriber pattern.

###Project Status

Main features are in testing phase. New features are still in development.

###Main features

* JSON-RPC 2.0 compatible, exposition of application functionalities. (Batch method call is not still supported).
* Real time data streaming support with built-in publish-subscribe pattern.
* Built-in client session control.
* Asynchronous messaging model.
* Message format (Text in Json-RPC format)
* Websocket full support: RFC6455.
* TLS support (through [websocket++](http://www.zaphoyd.com/websocketpp))
* Ipv6 support (through [websocket++](http://www.zaphoyd.com/websocketpp))

###Possible applications:

* Telemetry systems.
* Real time monitoring systems.
* Real time market data streaming.
* Data adquisition and [SCADA](http://en.wikipedia.org/wiki/SCADA) applications.
