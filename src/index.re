[%bs.raw {|require('./index.css')|}];
[%bs.raw {|require('./app.css')|}];
[%bs.raw {|require('tachyons/css/tachyons.css')|}];

[@bs.module "./registerServiceWorker"]
external register_service_worker : unit => unit = "default";

ReactDOMRe.renderToElementWithId(
  <ReasonApollo.Provider client=Client.instance>
    <ListMovies />
  </ReasonApollo.Provider>,
  "root",
);

register_service_worker();