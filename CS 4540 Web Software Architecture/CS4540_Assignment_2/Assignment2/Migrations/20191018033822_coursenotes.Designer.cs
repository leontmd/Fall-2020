﻿// <auto-generated />
using System;
using Assignment2.Models;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Infrastructure;
using Microsoft.EntityFrameworkCore.Metadata;
using Microsoft.EntityFrameworkCore.Migrations;
using Microsoft.EntityFrameworkCore.Storage.ValueConversion;

namespace Assignment2.Migrations
{
    [DbContext(typeof(LOContext))]
    [Migration("20191018033822_coursenotes")]
    partial class coursenotes
    {
        protected override void BuildTargetModel(ModelBuilder modelBuilder)
        {
#pragma warning disable 612, 618
            modelBuilder
                .HasAnnotation("ProductVersion", "2.2.3-servicing-35854")
                .HasAnnotation("Relational:MaxIdentifierLength", 128)
                .HasAnnotation("SqlServer:ValueGenerationStrategy", SqlServerValueGenerationStrategy.IdentityColumn);

            modelBuilder.Entity("Assignment2.Models.Course", b =>
                {
                    b.Property<int>("CourseId")
                        .ValueGeneratedOnAdd()
                        .HasAnnotation("SqlServer:ValueGenerationStrategy", SqlServerValueGenerationStrategy.IdentityColumn);

                    b.Property<string>("department");

                    b.Property<string>("description");

                    b.Property<int>("metricPercent");

                    b.Property<string>("name");

                    b.Property<int>("number");

                    b.Property<string>("professor");

                    b.Property<string>("professorEmail");

                    b.Property<string>("semeseter");

                    b.Property<int>("year");

                    b.HasKey("CourseId");

                    b.ToTable("Courses");
                });

            modelBuilder.Entity("Assignment2.Models.CourseNote", b =>
                {
                    b.Property<int>("CourseNoteId")
                        .ValueGeneratedOnAdd()
                        .HasAnnotation("SqlServer:ValueGenerationStrategy", SqlServerValueGenerationStrategy.IdentityColumn);

                    b.Property<int>("CourseNum");

                    b.Property<DateTime>("modifiedDate");

                    b.Property<string>("note");

                    b.Property<int?>("number");

                    b.Property<string>("status");

                    b.HasKey("CourseNoteId");

                    b.HasIndex("number");

                    b.ToTable("CourseNote");
                });

            modelBuilder.Entity("Assignment2.Models.LearningOutcome", b =>
                {
                    b.Property<int>("LearningOutcomeId")
                        .ValueGeneratedOnAdd()
                        .HasAnnotation("SqlServer:ValueGenerationStrategy", SqlServerValueGenerationStrategy.IdentityColumn);

                    b.Property<int>("CourseNum");

                    b.Property<string>("description");

                    b.Property<string>("name");

                    b.Property<int?>("number");

                    b.HasKey("LearningOutcomeId");

                    b.HasIndex("number");

                    b.ToTable("LearningOutcomes");
                });

            modelBuilder.Entity("Assignment2.Models.LearningOutcomeNote", b =>
                {
                    b.Property<int>("LearningOutcomeNoteId")
                        .ValueGeneratedOnAdd()
                        .HasAnnotation("SqlServer:ValueGenerationStrategy", SqlServerValueGenerationStrategy.IdentityColumn);

                    b.Property<int>("LOId");

                    b.Property<int?>("LearningOutcomeId");

                    b.Property<bool>("lastEditChair");

                    b.Property<DateTime>("modifiedDate");

                    b.Property<string>("note");

                    b.HasKey("LearningOutcomeNoteId");

                    b.HasIndex("LearningOutcomeId");

                    b.ToTable("LearningOutcomeNote");
                });

            modelBuilder.Entity("Assignment2.Models.CourseNote", b =>
                {
                    b.HasOne("Assignment2.Models.Course", "Course")
                        .WithMany()
                        .HasForeignKey("number");
                });

            modelBuilder.Entity("Assignment2.Models.LearningOutcome", b =>
                {
                    b.HasOne("Assignment2.Models.Course", "Course")
                        .WithMany("LearningOutcomes")
                        .HasForeignKey("number");
                });

            modelBuilder.Entity("Assignment2.Models.LearningOutcomeNote", b =>
                {
                    b.HasOne("Assignment2.Models.LearningOutcome", "LearningOutcome")
                        .WithMany()
                        .HasForeignKey("LearningOutcomeId");
                });
#pragma warning restore 612, 618
        }
    }
}
