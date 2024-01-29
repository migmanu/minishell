<h1 id="the-mish-project">The Mish Project</h1>
<p>This is the 42 Berlin School <code>minishell</code> project, written by [author 1][author 2], in accordance with the version number [version number] of the subject [include subject and link]. This project does not cover the bonus part of the subject. In total, it took us around four weeks to finish the whole thing.</p>
<h2 id="installation">Installation</h2>
<p>If you want to test our <code>minishell</code>, Mish, you can do so in both Linux and Max.</p>
<ul>
<li>Clone the repo into your system</li>
<li>run the <code>make</code> command and wait until <code>libft</code> is cloned and built</li>
<li>run <code>./minishell</code> to open Mish.</li>
</ul>
<h2 id="about-the-project">About the Project</h2>
<p>The <code>minishell</code> project requires students to develop a simple clone of Bash. It is also the first group project of the 42 Core Curriculum. From these two statements, we can easily identify the main challenges and goals of the task:</p>
<ul>
<li>Acquire a deep understanding of Bash inner workings.</li>
<li>Coordinate work with your teammate.</li>
</ul>
<p>We believe that without properly addressing and planning for these two challenges from the very beginning, <code>minishell</code> will quickly turn into what a lot of students call &quot;minihell.&quot;</p>
<h3 id="understanding-bash">Understanding Bash</h3>
<p>Released in 1989, Bash has by now acquired almost mythical status. It is a universal tool that every programmer should feel, at the very least, acquainted with, if not properly comfortable. Therefore, sources at your disposal are plenty. If you are a 42 student, we advise you to search Slack for resources provided by fellow students over the years. Be aware, the <code>minishell</code> subject has changed over time, so not all advice is relevant. Here is a list of some of the most mentioned and useful links:</p>
#### Repositories

- [Repo with cool explaination](https://github.com/maiadegraaf/minishell)
- [Evaluation sheet](https://github.com/wis-aerrajiy/school21-checklists/blob/update_minishell/ng_3_minishell.pdf)
  
#### How-to's / minishell specific articles

- [Minishell: Building a mini-bash (a @42 project)](https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218) | tutorial
- [List of edge cases to test for](https://docs.google.com/spreadsheets/d/1TDwyd-S0WBAXehgkrKQtBJ6zquQ4p6k7JfE5g3jICNA/edit#gid=0)
- [Another list of edge cases and expected behaviors](https://docs.google.com/spreadsheets/u/0/d/1uJHQu0VPsjjBkR4hxOeCMEt3AOM1Hp_SmUzPFhAH-nA/htmlview?lsrp=1#gid=0) | some are not expected by the project subject
- [High level explanation of the project](https://haglobah.github.io/Mastering-42/holy_graph/minishell.html) | has good sources
- [42 Slack char about how to implement history](https://42born2code.slack.com/archives/CN9RHKQHW/p1654165861713979)
  
#### On the shell

- [Really in-depth video series explanation of how the shell works](https://www.youtube.com/playlist?list=PLFAC320731F539902) | watch at 1.25x
- [Shell (computing) - Wikipedia](https://en.wikipedia.org/wiki/Shell_(computing))
- [Read-eval-print loop](https://en.wikipedia.org/wiki/Read%E2%80%93eval%E2%80%93print_loop) | Basic paradigm behind CLI
- [Writing your own shell](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf) | Extensive explanation of a shell written in C++
- [Shell syntax](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html)
- [Write your own shell](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf) | paper on how to write a shell which might apply better for a non-bonus minishell.
- [A lot of cool resources in one place.](https://minishell.simple.ink/)
  
#### On the allowed functions

- [General info from all the allowed functions (in Korean).](https://velog.io/@chez_bono/Minishell#%EA%B5%AC%ED%98%84%ED%95%B4%EC%95%BC-%ED%95%A0-%EB%B9%8C%ED%8A%B8%EC%9D%B8)
  
<p>In our experience, no amount of reading will actually prepare you for some of Bash&#39;s more obscure behaviors. And although a lot of them are out of the scope of the project, there&#39;s still plenty that needs to be considered, even if you do not go for the bonus. We encountered a lot of these difficult cases while testing our almost finished project. This is the most stressful way of discovering them. Luckily, by then our program was robust enough to withstand most of them.</p>
<p>Nevertheless, there are two available online spreadsheets that cover a huge amount of cases to test for. You can find them linked above. It's a good idea to go through most, if not all, of them at least once to test your <code>minishell</code>. Maybe a read before could avoid some issues down the line too. But <strong>be aware</strong>, a lot of the cases mentioned in these spreadsheets are out of scope, apply only for bonus or are outright wrong. Do not follow them blindly, but test each with Bash on your own.</p>

<h3 id="coordinating-teamwork">Coordinating Teamwork</h3>
<p>There was no great compleity regarding teamwork. Given the small size of the team and our generous time availability, we went through a simple workflow. Each change or bug fix was done inside a bransh of this repository, pushed, reviewd by the other author and merged. We could make this work because we communicated a lot, either through Slack or coding side by side.</p>
<p>Regardless of how you chose to organize work, you will need to communicate as much as possible and try to understand whats going on even inside the files you have not written.</p>
<h2 id="how-mish-works">How Mish Works</h2>
<p>After you&#39;ve read the listed sources, youll learn that Bash is composed of four distinct parts: the <code>parser</code>, the <code>tokenizer</code>, the <code>expander</code>, and the <code>executor</code>. Tokens are put into a tree, which is then executed in the appropiate order. This should probably be your layout if you are aiming for the bonus.</p>
<p>Otherwise things can be simplified a bit. Mish does not have a separate <code>expander</code>. Inside the <code>input_handler</code> directory .
There is no tree structure but a list of commands that gets executed from beginning to end.</p>
