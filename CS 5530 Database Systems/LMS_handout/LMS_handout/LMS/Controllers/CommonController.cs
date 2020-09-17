﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using LMS.Models.LMSModels;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

namespace LMS.Controllers
{
  public class CommonController : Controller
  {

    /*******Begin code to modify********/

    // TODO: Uncomment and change 'X' after you have scaffoled
    protected Team75LMSContext db;

    public CommonController()
    {
      db = new Team75LMSContext();
    }

    /*
     * WARNING: This is the quick and easy way to make the controller
     *          use a different LibraryContext - good enough for our purposes.
     *          The "right" way is through Dependency Injection via the constructor 
     *          (look this up if interested).
    */

    // TODO: Uncomment and change 'X' after you have scaffoled
    public void UseLMSContext(Team75LMSContext ctx)
    {
      db = ctx;
    }

    protected override void Dispose(bool disposing)
    {
      if (disposing)
      {
        db.Dispose();
      }
      base.Dispose(disposing);
    }



    /// <summary>
    /// Retreive a JSON array of all departments from the database.
    /// Each object in the array should have a field called "name" and "subject",
    /// where "name" is the department name and "subject" is the subject abbreviation.
    /// </summary>
    /// <returns>The JSON array</returns>
    public IActionResult GetDepartments()
    {
      var query =
        from d in db.Departments
        select new
        {
          name = d.Name,
          subject = d.Subject
        };
      return Json(query.ToArray());
    }
    
    /// <summary>
    /// Returns a JSON array representing the course catalog.
    /// Each object in the array should have the following fields:
    /// "subject": The subject abbreviation, (e.g. "CS")
    /// "dname": The department name, as in "Computer Science"
    /// "courses": An array of JSON objects representing the courses in the department.
    ///            Each field in this inner-array should have the following fields:
    ///            "number": The course number (e.g. 5530)
    ///            "cname": The course name (e.g. "Database Systems")
    /// </summary>
    /// <returns>The JSON array</returns>
    public IActionResult GetCatalog()
    {
      var query =
        from d in db.Departments
        select new
        {
          subject = d.Subject,
          dname = d.Name,
          courses = d.Courses.Select((key, index) => new { number = key.Num, cname = key.Name })
        };

      return Json(query.ToArray());
    }

    /// <summary>
    /// Returns a JSON array of all class offerings of a specific course.
    /// Each object in the array should have the following fields:
    /// "season": the season part of the semester, such as "Fall"
    /// "year": the year part of the semester
    /// "location": the location of the class
    /// "start": the start time in format "hh:mm:ss"
    /// "end": the end time in format "hh:mm:ss"
    /// "fname": the first name of the professor
    /// "lname": the last name of the professor
    /// </summary>
    /// <param name="subject">The subject abbreviation, as in "CS"</param>
    /// <param name="number">The course number, as in 5530</param>
    /// <returns>The JSON array</returns>
    public IActionResult GetClassOfferings(string subject, int number)
    {
      var query =
        from c in db.Classes
        where c.Catalog.Num == number
        where c.Catalog.Department == subject
        select new
        {
          season = c.Semester.Substring(0, c.Semester.IndexOf(" ")),
          year = c.Semester.Substring(c.Semester.IndexOf(" ") + 1),
          location = c.Location,
          start = c.Start,
          end = c.End,
          fname = c.ProfessorNavigation.FName,
          lname = c.ProfessorNavigation.LName
        };

      return Json(query.ToArray());
    }

    /// <summary>
    /// This method does NOT return JSON. It returns plain text (containing html).
    /// Use "return Content(...)" to return plain text.
    /// Returns the contents of an assignment.
    /// </summary>
    /// <param name="subject">The course subject abbreviation</param>
    /// <param name="num">The course number</param>
    /// <param name="season">The season part of the semester for the class the assignment belongs to</param>
    /// <param name="year">The year part of the semester for the class the assignment belongs to</param>
    /// <param name="category">The name of the assignment category in the class</param>
    /// <param name="asgname">The name of the assignment in the category</param>
    /// <returns>The assignment contents</returns>
    public IActionResult GetAssignmentContents(string subject, int num, string season, int year, string category, string asgname)
    {
      var query =
        from a in db.Assignments
        join cat in db.AssignmentCategories
        on a.CatId equals cat.CatId
        join c in db.Classes
        on cat.ClassId equals c.ClassId
        where c.Catalog.Num == num
        where c.Catalog.Department == subject
        where c.Semester == season + " " + year
        where cat.Name == category
        where a.Name == asgname
        select new
        {
          contents = a.Contents
        };

      // Hack to make the query evaluate, otherwise false negatives on length / on null
      var content = query.ToArray().Length == 0 ? "" : query.FirstOrDefault().contents;
      return Content(content);
    }


    /// <summary>
    /// This method does NOT return JSON. It returns plain text (containing html).
    /// Use "return Content(...)" to return plain text.
    /// Returns the contents of an assignment submission.
    /// Returns the empty string ("") if there is no submission.
    /// </summary>
    /// <param name="subject">The course subject abbreviation</param>
    /// <param name="num">The course number</param>
    /// <param name="season">The season part of the semester for the class the assignment belongs to</param>
    /// <param name="year">The year part of the semester for the class the assignment belongs to</param>
    /// <param name="category">The name of the assignment category in the class</param>
    /// <param name="asgname">The name of the assignment in the category</param>
    /// <param name="uid">The uid of the student who submitted it</param>
    /// <returns>The submission text</returns>
    public IActionResult GetSubmissionText(string subject, int num, string season, int year, string category, string asgname, string uid)
    {
      var query =
        from s in db.Submissions
        join a in db.Assignments
        on s.AId equals a.AId
        join ct in db.AssignmentCategories
        on a.CatId equals ct.CatId
        join c in db.Classes
        on ct.ClassId equals c.ClassId
        where c.Catalog.Num == num
        where c.Catalog.Department == subject
        where c.Semester == season + " " + year
        where ct.Name == category
        where a.Name == asgname
        where s.UId == uid
        select new
        {
          contents = s.Contents
        };

      // Hack to make the query evaluate, otherwise false negatives on length / on null
      var content = query.ToArray().Length == 0 ? "" : query.FirstOrDefault().contents;
      return Content(content);
    }


    /// <summary>
    /// Gets information about a user as a single JSON object.
    /// The object should have the following fields:
    /// "fname": the user's first name
    /// "lname": the user's last name
    /// "uid": the user's uid
    /// "department": (professors and students only) the name (such as "Computer Science") of the department for the user. 
    ///               If the user is a Professor, this is the department they work in.
    ///               If the user is a Student, this is the department they major in.    
    ///               If the user is an Administrator, this field is not present in the returned JSON
    /// </summary>
    /// <param name="uid">The ID of the user</param>
    /// <returns>
    /// The user JSON object 
    /// or an object containing {success: false} if the user doesn't exist
    /// </returns>
    public IActionResult GetUser(string uid)
    {
      try
      {
        var q1 =
          from s in db.Students
          where s.UId == uid
          select new
          {
            fname = s.FName,
            lname = s.LName,
            uid = s.UId,
            department = s.MajorNavigation.Name
          };

        var q2 =
          from p in db.Professors
          where p.UId == uid
          select new
          {
            fname = p.FName,
            lname = p.LName,
            uid = p.UId,
            department = p.DepartmentNavigation.Name
          };

        var q3 =
          from a in db.Administrators
          where a.UId == uid
          select new
          {
            fname = a.FName,
            lname = a.LName,
            uid = a.UId
          };

        if (q1 != null) return Json(q1.FirstOrDefault());
        if (q2 != null) return Json(q2.FirstOrDefault());
        if (q3 != null) return Json(q3.FirstOrDefault());

        return Json(new { success = false });
      }
      catch (Exception e)
      {
        return Json(new { success = false });
      }
    }


    /*******End code to modify********/

  }
}