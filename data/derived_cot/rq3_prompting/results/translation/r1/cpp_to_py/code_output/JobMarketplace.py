from typing import List

class Job:
    def __init__(self, job_title: str, company: str, requirements: List[str]):
        self.job_title = job_title
        self.company = company
        self.requirements = requirements

    def __eq__(self, other: 'Job') -> bool:
        if not isinstance(other, Job):
            return NotImplemented
        return (self.job_title == other.job_title and
                self.company == other.company and
                self.requirements == other.requirements)


class Resume:
    def __init__(self, name: str, skills: List[str], experience: str):
        self.name = name
        self.skills = skills
        self.experience = experience

    def __eq__(self, other: 'Resume') -> bool:
        if not isinstance(other, Resume):
            return NotImplemented
        return (self.name == other.name and
                self.skills == other.skills and
                self.experience == other.experience)


class JobMarketplace:
    def __init__(self):
        self.job_listings: List[Job] = []
        self.resumes: List[Resume] = []

    def post_job(self, job_title: str, company: str, requirements: List[str]) -> None:
        self.job_listings.append(Job(job_title, company, requirements))

    def remove_job(self, job: Job) -> None:
        self.job_listings = [j for j in self.job_listings if j != job]

    def submit_resume(self, name: str, skills: List[str], experience: str) -> None:
        self.resumes.append(Resume(name, skills, experience))

    def withdraw_resume(self, resume: Resume) -> None:
        self.resumes = [r for r in self.resumes if r != resume]

    def search_jobs(self, criteria: str) -> List[Job]:
        matching_jobs: List[Job] = []
        for job in self.job_listings:
            found = criteria in job.job_title
            if not found:
                for req in job.requirements:
                    if criteria in req:
                        found = True
                        break
            if found:
                matching_jobs.append(job)
        return matching_jobs

    def get_job_applicants(self, job: Job) -> List[Resume]:
        applicants: List[Resume] = []
        for resume in self.resumes:
            if JobMarketplace.matches_requirements(resume, job.requirements):
                applicants.append(resume)
        return applicants

    @staticmethod
    def matches_requirements(resume: Resume, requirements: List[str]) -> bool:
        for skill in resume.skills:
            if skill not in requirements:
                return False
        return True