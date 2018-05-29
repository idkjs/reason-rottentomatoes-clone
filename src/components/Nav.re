let component = ReasonReact.statelessComponent("Nav");

let make = _children => {
  ...component,
  render: _self =>
    <nav className="navbar navbar-default">
      <div className="navbar-header">
        <Link className="navbar-brand" href="/">
          ("Rotten Tomatoes" |> Utils.ste)
        </Link>
      </div>
      <ul className="nav navbar-nav">
        <li>
          <Link className="whatever" href="/">
            ("All Movie Ratings" |> Utils.ste)
          </Link>
        </li>
      </ul>
    </nav>,
  /* <li>{isLoggedIn() ? <Link href="/create">Add Movies</Link> : ""}</li> */
  /* <ul className="nav navbar-nav navbar-right">
       <li>
         {isLoggedIn() ? (
           <button className="btn btn-danger log" onClick={() => logout()}>
             Log out{" "}
           </button>
         ) : (
           <button className="btn btn-info log" onClick={() => login()}>
             Log In
           </button>
         )}
       </li>
     </ul> */
};