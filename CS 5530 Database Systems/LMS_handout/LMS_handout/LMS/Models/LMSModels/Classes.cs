﻿using System;
using System.Collections.Generic;

namespace LMS.Models.LMSModels
{
    public partial class Classes
    {
        public Classes()
        {
            AssignmentCategories = new HashSet<AssignmentCategories>();
            Enrolled = new HashSet<Enrolled>();
        }

        public string Semester { get; set; }
        public string Location { get; set; }
        public TimeSpan? Start { get; set; }
        public TimeSpan? End { get; set; }
        public string Professor { get; set; }
        public uint CatalogId { get; set; }
        public uint ClassId { get; set; }

        public virtual Courses Catalog { get; set; }
        public virtual Professors ProfessorNavigation { get; set; }
        public virtual ICollection<AssignmentCategories> AssignmentCategories { get; set; }
        public virtual ICollection<Enrolled> Enrolled { get; set; }
    }
}
