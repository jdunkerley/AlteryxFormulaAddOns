using System;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Security.Principal;

namespace InstallAlteryxAbacus
{
    class Program
    {
        private const string Elev = "ELEV";

        static int Main(string[] args)
        {
            int exitCode = DoMain(args);
            //Console.ReadLine();
            return exitCode;
        }

        private static int DoMain(string[] args)
        {
            if (args.Length < 2)
            {
                Console.WriteLine("Syntax: <SourcePattern1> [SourcePattern2] ... [SourcePatternN] <Output>");
                return -1;
            }

            bool loop = args[0] == Elev;

            var files =
                args.Take(args.Length - 1)
                    .Where(a => !string.IsNullOrWhiteSpace(a) && a != Elev)
                    .SelectMany(a => loop ? new[] {a} : Directory.GetFiles(Path.GetDirectoryName(a), Path.GetFileName(a)))
                    .ToArray();

            var destPath = args.Last();
            try
            {
                foreach (var file in files)
                {
                    string destFileName = Path.Combine(destPath, Path.GetFileName(file));
                    File.Copy(file, destFileName, true);
                    Console.WriteLine("Copied to " + destFileName);
                }
            }
            catch (UnauthorizedAccessException auth)
            {
                if (!loop && !IsElevated)
                {
                    var processInfo = new ProcessStartInfo
                                          {
                                              Verb = "runas",
                                              FileName = System.Reflection.Assembly.GetExecutingAssembly().Location,
                                              Arguments = $"{Elev} {String.Join(" ", files.Select(a => $"\"{a}\""))} \"{destPath}\""
                                          };

                    var proc = Process.Start(processInfo);
                    if (proc != null)
                    {
                        proc.WaitForExit();
                        return proc.ExitCode;
                    }
                }

                Console.WriteLine("Unauthorized Exception: " + auth.Message);
                return -1;
            }
            catch (Exception ex)
            {
                Console.WriteLine("Exception: " + ex.Message);
                return -2;
            }

            return 0;

        }

        public static bool IsElevated
        {
            get
            {
                var id = WindowsIdentity.GetCurrent();
                return id.Owner != id.User;
            }
        }

        public static bool IsAdministrator()
            => new WindowsPrincipal(WindowsIdentity.GetCurrent()).IsInRole(WindowsBuiltInRole.Administrator);
    }
}
