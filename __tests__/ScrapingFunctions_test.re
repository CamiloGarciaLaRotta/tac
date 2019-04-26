open Jest;

open Expect;

open ScrapingFunctions;

describe("Validation Functions", () => {
  describe("validateNonNull", () => {
    let value = "something";
    let someValue = Js.Option.some(value);
    test("with something", () =>
      validateNonNull(someValue) |> expect |> toBe(value)
    );
    test("with nothing", () =>
      try (validateNonNull(None)) {
      | Failure("Value is null") => pass
      | _ => fail("expected failure")
      }
    );
  });
  describe("validateUrl", () => {
    let httpsUrl = "https://github.com/scrum-gang/jobhub-chrome/pull/27";
    let httpUrl = "http://github.com/scrum-gang/jobhub-chrome/pull/27";
    let someHttpsURL = Js.Option.some(httpsUrl);
    let someHttpURL = Js.Option.some(httpUrl);
    test("https", () =>
      validateUrl(someHttpsURL) |> expect |> toBe(httpsUrl)
    );
    test("http", () =>
      validateUrl(someHttpURL) |> expect |> toBe(httpUrl)
    );
  });
  describe("checkValidUrl", () =>
    test("empty string", () => {
      /** TODO: there has to be a more elegant way to test failures.... */
      let expectedFailure = "Invalid URL";
      let caughtFailure =
        try (checkValidUrl("")) {
        | Failure(expectedFailure) => expectedFailure
        | _ => ""
        };
      caughtFailure == expectedFailure ? pass : fail("expected failure");
    })
  );
});

describe("Process Functions", () =>
  describe("toStringProcess", () => {
    test("number", () =>
      toStringProcess(3.5) |> expect |> toBe("3.5")
    );
    test("array", () =>
      toStringProcess([|1, 2, 3|]) |> expect |> toBe("1,2,3")
    );
    test("none", () =>
      toStringProcess(None) |> expect |> toBe("undefined")
    );
  })
);

describe("Date Functions", () => {
  describe("formatDate", () => {
    /** TODO: add invalid cases */
    let pastDate =
      Js.Date.makeWithYMD(~year=1970.0, ~month=0.0, ~date=1.0, ());
    let futureDate =
      Js.Date.makeWithYMD(~year=2020.0, ~month=10.0, ~date=13.0, ());
    let floatPastDate = pastDate |> Js.Date.getTime;
    let floatFutureDate = futureDate |> Js.Date.getTime;
    test("future date", () =>
      formatDate(floatPastDate) |> expect |> toBe("1970-01-01")
    );
    test("past date", () =>
      formatDate(floatFutureDate) |> expect |> toBe("2020-11-13")
    );
  });
  describe("daysAgoDate", () => {
    let now = Js.Date.make();
    let today = now |> Js.Date.getTime;
    /** must pass a new Js.Date.t everytime because setDate changes the passed date */
    let minus5DaysAgo =
      Js.Date.setDate(Js.Date.make(), Js.Date.getDate(now) -. 5.0);
    let plus10DaysAgo =
      Js.Date.setDate(Js.Date.make(), Js.Date.getDate(now) +. 10.0);
    let minus160DaysAgo =
      Js.Date.setDate(Js.Date.make(), Js.Date.getDate(now) -. 160.0);
    test("0 days ago", () =>
      daysAgoDate("0") |> expect |> toBe(today |> formatDate)
    );
    test("5 days in the future", () =>
      daysAgoDate("5") |> expect |> toBe(minus5DaysAgo |> formatDate)
    );
    test("160 days ago", () =>
      daysAgoDate("160") |> expect |> toBe(minus160DaysAgo |> formatDate)
    );
    test("5 days in the future", () =>
      daysAgoDate("-10") |> expect |> toBe(plus10DaysAgo |> formatDate)
    );
  });
  let stringWithDate = "Lorem ipsum dolor sit 9 days ago, consectetur";
  let stringWithoutDate = "Lorem ipsum dolor sit, consectetur";
  describe("extractPostedDateProcess", () => {
    test("contains date", () =>
      extractPostedDateProcess(stringWithDate)
      |> Js.String.length
      |> expect
      |> toEqual(10)
    );
    test("does not contain date", () =>
      extractPostedDateProcess(stringWithoutDate)
      |> Js.String.length
      |> expect
      |> toEqual(0)
    );
  });
  describe("validateDate", () => {
    let optionWithDate = Js.Option.some(stringWithDate);
    let lengthString = Js.String.length(stringWithDate);
    test("valid date", () =>
      validateDate(optionWithDate)
      |> Js.String.length
      |> expect
      |> toEqual(lengthString)
    );
    test("no date", () => {
      /** TODO: there has to be a more elegant way to test failures.... */
      let expectedFailure = "Unable to find posted date";
      let caughtFailure = {
        let someInvalidDate = Js.Option.some("");
        try (validateDate(someInvalidDate)) {
        | Failure(expectedFailure) => expectedFailure
        | _ => ""
        };
      };
      caughtFailure == expectedFailure ? pass : fail("expected failure");
    });
  });
});
