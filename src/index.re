[%bs.raw {|require('./index.css')|}];

[@bs.module "./registerServiceWorker"]
external register_service_worker : unit => unit = "default";

ReactDOMRe.renderToElementWithId(
  <ReasonApollo.Provider client=Client.instance>
    <App message="ReasonReact Graphql MoviesDB" />
  </ReasonApollo.Provider>,
  "root",
);

register_service_worker();